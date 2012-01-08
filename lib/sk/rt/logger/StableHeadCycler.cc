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
#include <sk/util/SystemException.h>

#include "StableHeadCycler.h"
#include <unistd.h>

sk::rt::logger::StableHeadCycler::
StableHeadCycler(const sk::util::Pathname& pathname)
  : AbstractCycler(pathname), _nextChunk(0)
{
}

sk::rt::logger::StableHeadCycler::
~StableHeadCycler()
{
}

bool
sk::rt::logger::StableHeadCycler::
scanFile()
{
  return readMarker(getPath(), _nextChunk);
}

void
sk::rt::logger::StableHeadCycler::
initFile()
{
  writeMarker(getPath(), _nextChunk);
}

void
sk::rt::logger::StableHeadCycler::
cycleFile()
{
  sk::util::String backup = makeChunkPath(_nextChunk);
  unlink(backup.getChars());
  if(rename(getPath().getChars(), backup.getChars()) < 0) {
    throw sk::util::SystemException(sk::util::String("rename():") + getPath());
  }
  _nextChunk += 1;

  int chunks = getChunks();
  if(chunks > 0) {
    if(_nextChunk >= chunks) {
      _nextChunk = 0;
    }
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

sk::util::Object*
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

