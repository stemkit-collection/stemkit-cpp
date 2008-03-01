/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/IllegalStateException.h>
#include <sk/util/NumberFormatException.h>
#include <sk/util/SystemException.h>

#include <logger/FileDestination.h>
#include <unistd.h>

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname)
  : _nextBackup(0), _bytesWritten(0), _fileHolder(new std::fstream),
    _pathname(pathname), _size(0), _backups(0)
{
  _fileHolder.get().exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
}

sk::rt::logger::FileDestination::
~FileDestination()
{
}

const sk::util::Class
sk::rt::logger::FileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::FileDestination");
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

void
sk::rt::logger::FileDestination::
makeReady()
{
  if(_bytesWritten == 0) {
    openFile();
  }
}

void
sk::rt::logger::FileDestination::
dispatch(const char* buffer, int size)
{
  makeReady();

  _fileHolder.get().write(buffer, size);
  _fileHolder.get().flush();
  
  if(_size > 0) {
    _bytesWritten += size;
    if(_bytesWritten > _size) {
      _fileHolder.get() << "[---Switched---]" << std::endl;

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
  _fileHolder.get().open(_pathname.toString().getChars(), std::ios::in | std::ios::out);
  _fileHolder.get().seekp(0, std::ios::end);
  _bytesWritten = _fileHolder.get().tellp();
}

void
sk::rt::logger::FileDestination::
closeFile()
{
  try {
    _fileHolder.get().close();
  }
  catch(...) {}

  _fileHolder.get().clear();
}

void
sk::rt::logger::FileDestination::
backupFile()
{
  sk::util::String backup = _pathname.toString() + '-' + sk::util::Integer::toString(_nextBackup);
  unlink(backup.getChars());
  if(link(_pathname.toString().getChars(), backup.getChars()) < 0) {
    throw sk::util::SystemException("link()");
  }
  if(unlink(_pathname.toString().getChars()) < 0) {
    throw sk::util::SystemException("unlink()");
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
  file << '[' << _pathname.basename() << '-' << _nextBackup << " of " << _backups << ']' << std::endl;

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
    sk::util::String format = '[' + _pathname.basename() + "-%d of %d" + ']';
    int backups;

    if(sscanf(line.getChars(), format.getChars(), &_nextBackup, &backups) == 2) {
      return true;
    }
  }
  return false;
}
