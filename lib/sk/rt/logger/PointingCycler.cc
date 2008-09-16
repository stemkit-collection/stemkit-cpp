/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include "PointingCycler.h"

sk::rt::logger::PointingCycler::
PointingCycler(const sk::util::Pathname& pathname)
  : AbstractCycler(pathname)
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

sk::rt::logger::PointingCycler*
sk::rt::logger::PointingCycler::
clone() const 
{
  return new PointingCycler(*this);
}

bool 
sk::rt::logger::PointingCycler::
isTop() const
{
  throw sk::util::UnsupportedOperationException("isTop()");
}

void 
sk::rt::logger::PointingCycler::
initChunk()
{
  throw sk::util::UnsupportedOperationException("initChunk()");
}

bool 
sk::rt::logger::PointingCycler::
advance(off_t)
{
  throw sk::util::UnsupportedOperationException("advance()");
}

const sk::util::String 
sk::rt::logger::PointingCycler::
getPath() const
{
  throw sk::util::UnsupportedOperationException("getPath()");
}
