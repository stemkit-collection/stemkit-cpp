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
#include <sk/util/SystemException.h>
#include <sk/util/IllegalStateException.h>

#include <fstream>

#include "StableHeadCycler.h"

sk::rt::logger::StableHeadCycler::
StableHeadCycler(const sk::util::Pathname& pathname)
  : AbstractCycler(pathname), _nextChunk(0)
{
}

sk::rt::logger::StableHeadCycler::
~StableHeadCycler()
{
}

void
sk::rt::logger::StableHeadCycler::
init() 
{
  if(scanFile() == false) {
    initFile();
  }
}

bool
sk::rt::logger::StableHeadCycler::
scanFile()
{
  std::ifstream file(getPath().getChars());
  if(file.good() == false)  {
    return false;
  }
  sk::util::String line;
  if(std::getline(file, line).good() == true) {
    sk::util::String format = '[' + getPathname().basename() + " %d of %d" + ']';
    int chunks;

    if(sscanf(line.getChars(), format.getChars(), &_nextChunk, &chunks) == 2) {
      return true;
    }
  }
  return false;
}

void
sk::rt::logger::StableHeadCycler::
initFile()
{
  std::ofstream file(getPath().getChars());
  if(file.good() == false) {
    throw sk::util::SystemException("Cannot access " + getPath().inspect());
  }
  file << '[' << getPathname().basename() << ' ' << _nextChunk << " of " << getChunks() << ']' << std::endl;

  if(file.good() == false) {
    throw sk::util::IllegalStateException("Cannot initialize " + getPath().inspect());
  }
}

void
sk::rt::logger::StableHeadCycler::
cycleFile()
{
  sk::util::String backup = getPath() + '-' + sk::util::Integer::toString(_nextChunk);
  unlink(backup.getChars());
  if(rename(getPath().getChars(), backup.getChars()) < 0) {
    throw sk::util::SystemException(sk::util::String("rename():") + getPath());
  }
  _nextChunk += 1;
  if(_nextChunk >= getChunks()) {
    _nextChunk = 0;
  }
}

const sk::util::String
sk::rt::logger::StableHeadCycler::
getPath() const
{
  return getPathname().toString();
}

const sk::util::Pathname&
sk::rt::logger::StableHeadCycler::
getPathname() const
{
  return getMasterPathname();
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

