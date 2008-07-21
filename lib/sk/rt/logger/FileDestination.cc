/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/NumberFormatException.h>
#include <sk/util/SystemException.h>

#include <logger/FileDestination.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname)
  : _nextBackup(0), _bytesWritten(0), _descriptor(-1),
    _pathname(pathname), _size(2048), _backups(3)
{
}

sk::rt::logger::FileDestination::
FileDestination(const FileDestination& other)
  : _nextBackup(other._nextBackup), _bytesWritten(other._bytesWritten), _descriptor(other.cloneDescriptor()),
    _pathname(other._pathname), _size(other._size), _backups(other._backups)
{
}

sk::rt::logger::FileDestination::
~FileDestination()
{
  closeFile();
}

int
sk::rt::logger::FileDestination::
cloneDescriptor() const
{
  return _descriptor < 0 ? _descriptor : dup(_descriptor);
}

const sk::util::Class
sk::rt::logger::FileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::FileDestination");
}

int
sk::rt::logger::FileDestination::
getSize() const
{
  return _size;
}

int 
sk::rt::logger::FileDestination::
getBackups() const
{
  return _backups;
}

void
sk::rt::logger::FileDestination::
setSize(const sk::util::String& specification)
{
  try {
    _size = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
setSize(int size)
{
  _size = size;
}

void
sk::rt::logger::FileDestination::
setBackups(const sk::util::String& specification)
{
  try {
    _backups = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
setBackups(int backups)
{
  _backups = backups;
}

sk::rt::logger::FileDestination*
sk::rt::logger::FileDestination::
clone() const
{
  return new FileDestination(*this);
}

const std::vector<int>
sk::rt::logger::FileDestination::
makeReady()
{
  static std::vector<int> descriptors;
  if(_bytesWritten == 0) {
    openFile();

    descriptors.clear();
    descriptors.push_back(_descriptor);
  }
  return descriptors;
}

void
sk::rt::logger::FileDestination::
dispatch(const char* buffer, int size)
{
  if(_bytesWritten == 0) {
    openFile();
  }
  writeData(buffer, size);

  if(_size > 0) {
    _bytesWritten += size;
    if(_bytesWritten > _size) {
      writeData("[---Switched---]\n");

      closeFile();
      backupFile();
      initFile();

      _bytesWritten = 0;
    }
  }
  else {
    _bytesWritten = 1;
  }
}

void
sk::rt::logger::FileDestination::
openFile()
{
  closeFile();

  if(scanFile() == false) {
    initFile();
  }
  _descriptor = ::open(_pathname.toString().getChars(), O_RDWR);
  if(_descriptor < 0) {
    throw sk::util::SystemException(sk::util::String("open():") + _pathname.toString());
  }
  off_t offset = ::lseek(_descriptor, 0, SEEK_END);
  if(offset == -1) {
    throw sk::util::SystemException(sk::util::String("lseek():") + _pathname.toString());
  }
  _bytesWritten = offset;
}

void
sk::rt::logger::FileDestination::
closeFile()
{
  if(_descriptor < 0) {
    return;
  }
  ::close(_descriptor);
  _descriptor = -1;
}

void
sk::rt::logger::FileDestination::
backupFile()
{
  sk::util::String backup = _pathname.toString() + '-' + sk::util::Integer::toString(_nextBackup);
  unlink(backup.getChars());
  if(rename(_pathname.toString().getChars(), backup.getChars()) < 0) {
    throw sk::util::SystemException(sk::util::String("rename():") + _pathname.toString());
  }
  _nextBackup += 1;
  if(_nextBackup >= _backups) {
    _nextBackup = 0;
  }
}

void
sk::rt::logger::FileDestination::
initFile()
{
  std::ofstream file(_pathname.toString().getChars());
  if(file.good() == false) {
    throw sk::util::SystemException("Cannot access " + _pathname.toString().inspect());
  }
  file << '[' << _pathname.basename() << ' ' << _nextBackup << " of " << _backups << ']' << std::endl;

  if(file.good() == false) {
    throw sk::util::IllegalStateException("Cannot initialize " + _pathname.toString().inspect());
  }
}

bool
sk::rt::logger::FileDestination::
scanFile()
{
  std::ifstream file(_pathname.toString().getChars());
  if(file.good() == false)  {
    return false;
  }
  sk::util::String line;
  if(std::getline(file, line).good() == true) {
    sk::util::String format = '[' + _pathname.basename() + " %d of %d" + ']';
    int backups;

    if(sscanf(line.getChars(), format.getChars(), &_nextBackup, &backups) == 2) {
      return true;
    }
  }
  return false;
}

void
sk::rt::logger::FileDestination::
writeData(const char* data)
{
  writeData(data, strlen(data));
}

void
sk::rt::logger::FileDestination::
writeData(const char* data, int size)
{
  if(_descriptor < 0) {
    throw sk::util::IllegalStateException(sk::util::String("File not open:") + _pathname.toString());
  }
  int offset = 0;
  while(offset < size) {
    int n = ::write(_descriptor, data + offset, size - offset);
    if(n > 0) {
      offset += n;
      continue;
    }
    if(n == 0) {
      throw sk::util::IllegalStateException(sk::util::String("Write 0 bytes:") + _pathname.toString());
    }
    if(n < 0) {
      throw sk::util::SystemException(sk::util::String("write():") + _pathname.toString());
    }
  }
}
