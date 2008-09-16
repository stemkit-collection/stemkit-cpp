/*  vim: set sw=2:
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/NumberFormatException.h>
#include <sk/util/SystemException.h>
#include <sk/util/IllegalStateException.h>

#include <fstream>

#include "StableHeadCycler.h"

sk::rt::logger::StableHeadCycler::
StableHeadCycler(const sk::util::Pathname& pathname)
  : _nextBackup(0), _bytesWritten(0), _size(2048), _backups(3), _pathname(pathname)
{
}

sk::rt::logger::StableHeadCycler::
~StableHeadCycler()
{
}

bool
sk::rt::logger::StableHeadCycler::
isTop() const
{
  return _bytesWritten == 0;
}

bool
sk::rt::logger::StableHeadCycler::
advance(off_t size)
{
  if(_size > 0) {
    _bytesWritten += size;
    if(_bytesWritten > _size) {
      backupFile();
      initFile();

      _bytesWritten = 0;
      return false;
    }
  }
  else {
    _bytesWritten = 1;
  }
  return true;
}

void
sk::rt::logger::StableHeadCycler::
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
sk::rt::logger::StableHeadCycler::
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
sk::rt::logger::StableHeadCycler::
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
sk::rt::logger::StableHeadCycler::
initChunk() 
{
  if(scanFile() == false) {
    initFile();
  }
}

const sk::util::String
sk::rt::logger::StableHeadCycler::
getPath() const
{
  return _pathname.toString().getChars();
}

sk::rt::logger::StableHeadCycler*
sk::rt::logger::StableHeadCycler::
clone() const
{
  return new StableHeadCycler(*this);
}

const sk::util::Class
sk::rt::logger::StableHeadCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::StableHeadCycler");
}

int
sk::rt::logger::StableHeadCycler::
getSize() const
{
  return _size;
}

int 
sk::rt::logger::StableHeadCycler::
getBackups() const
{
  return _backups;
}

void
sk::rt::logger::StableHeadCycler::
setSize(const sk::util::String& specification)
{
  try {
    _size = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::StableHeadCycler::
setSize(int size)
{
  _size = size;
}

void
sk::rt::logger::StableHeadCycler::
setBackups(const sk::util::String& specification)
{
  try {
    _backups = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::StableHeadCycler::
setBackups(int backups)
{
  _backups = backups;
}

