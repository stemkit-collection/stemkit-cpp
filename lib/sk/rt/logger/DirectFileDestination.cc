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
#include <sk/util/SystemException.h>

#include <sk/rt/logger/DirectFileDestination.h>
#include <unistd.h>

sk::rt::logger::DirectFileDestination::
DirectFileDestination(const sk::util::Pathname& pathname)
  : FileDestination(pathname), _nextBackup(0), _bytesWritten(0), _fileHolder(new std::fstream)
{
  _fileHolder.get().exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
}

sk::rt::logger::DirectFileDestination::
~DirectFileDestination()
{
}

const sk::util::Class
sk::rt::logger::DirectFileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::DirectFileDestination");
}

sk::rt::logger::DirectFileDestination*
sk::rt::logger::DirectFileDestination::
clone() const
{
  return new DirectFileDestination(*this);
}

void
sk::rt::logger::DirectFileDestination::
makeReady()
{
  if(_bytesWritten == 0) {
    openFile();
  }
}

void
sk::rt::logger::DirectFileDestination::
dispatch(const char* buffer, int size)
{
  makeReady();

  _fileHolder.get().write(buffer, size);
  _fileHolder.get().flush();
  
  if(getSize() > 0) {
    _bytesWritten += size;
    if(_bytesWritten > getSize()) {
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
sk::rt::logger::DirectFileDestination::
openFile()
{
  closeFile();

  if(scanFile() == false) {
    initFile();
  }
  _fileHolder.get().open(getPathname().toString().getChars(), std::ios::in | std::ios::out);
  _fileHolder.get().seekp(0, std::ios::end);
  _bytesWritten = _fileHolder.get().tellp();
}

void
sk::rt::logger::DirectFileDestination::
closeFile()
{
  try {
    _fileHolder.get().close();
  }
  catch(...) {}

  _fileHolder.get().clear();
}

void
sk::rt::logger::DirectFileDestination::
backupFile()
{
  sk::util::String backup = getPathname().toString() + '-' + sk::util::Integer::toString(_nextBackup);
  unlink(backup.getChars());
  if(link(getPathname().toString().getChars(), backup.getChars()) < 0) {
    throw sk::util::SystemException("link()");
  }
  if(unlink(getPathname().toString().getChars()) < 0) {
    throw sk::util::SystemException("unlink()");
  }
  _nextBackup += 1;
  if(_nextBackup >= getBackups()) {
    _nextBackup = 0;
  }
}

void
sk::rt::logger::DirectFileDestination::
initFile()
{
  std::ofstream file(getPathname().toString().getChars());
  if(file.good() == false) {
    throw sk::util::SystemException("Cannot access " + getPathname().toString().inspect());
  }
  file << '[' << getPathname().basename() << '-' << _nextBackup << " of " << getBackups() << ']' << std::endl;

  if(file.good() == false) {
    throw sk::util::IllegalStateException("Cannot initialize " + getPathname().toString().inspect());
  }
}

bool
sk::rt::logger::DirectFileDestination::
scanFile()
{
  std::ifstream file(getPathname().toString().getChars());
  if(file.good() == false)  {
    return false;
  }
  sk::util::String line;
  if(std::getline(file, line).good() == true) {
    sk::util::String format = '[' + getPathname().basename() + "-%d of %d" + ']';
    int backups;

    if(sscanf(line.getChars(), format.getChars(), &_nextBackup, &backups) == 2) {
      return true;
    }
  }
  return false;
}
