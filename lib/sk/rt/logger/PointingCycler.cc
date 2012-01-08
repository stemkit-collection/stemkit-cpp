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
#include <sk/util/File.h>

#include "PointingCycler.h"

sk::rt::logger::PointingCycler::
PointingCycler(const sk::util::Pathname& pathname)
  : AbstractCycler(pathname), _chunk(1)
{
}

sk::rt::logger::PointingCycler::
~PointingCycler()
{
}

const sk::util::Class
sk::rt::logger::PointingCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::PointingCycler");
}

sk::util::Object*
sk::rt::logger::PointingCycler::
clone() const
{
  return new PointingCycler(*this);
}

const sk::util::String
sk::rt::logger::PointingCycler::
getPath() const
{
  return makeChunkPath(_chunk);
}

bool
sk::rt::logger::PointingCycler::
scanFile()
{
  int masterChunk;
  int chunk;

  if(readMarker(getMasterPathname().toString(), masterChunk) == true) {
    if(readMarker(makeChunkPath(masterChunk), chunk) == true) {
      if(masterChunk == chunk) {
        _chunk = chunk;
        return true;
      }
    }
  }
  return false;
}

void
sk::rt::logger::PointingCycler::
initFile()
{
  writeMarker(getMasterPathname().toString(), _chunk);
  writeMarker(getPath(), _chunk);
}

void
sk::rt::logger::PointingCycler::
cycleFile()
{
  _chunk += 1;

  int chunks = getChunks();
  if(chunks > 0) {
    if(_chunk > chunks) {
      _chunk = 1;
    }
  }
}

void
sk::rt::logger::PointingCycler::
ensureChunks()
{
  sk::util::File::create(getMasterPathname().toString());
  for(int chunk=0; chunk < getChunks() ;++chunk) {
    sk::util::File::create(makeChunkPath(chunk + 1));
  }
}
