/*  vi: set sw=2:
 *
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

#include "AbstractCycler.h"

sk::rt::logger::AbstractCycler::
AbstractCycler(const sk::util::Pathname& masterPathname)
  : _masterPathname(masterPathname)
{
}

sk::rt::logger::AbstractCycler::
~AbstractCycler()
{
}

const sk::util::Class
sk::rt::logger::AbstractCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::AbstractCycler");
}

const sk::util::Pathname&
sk::rt::logger::AbstractCycler::
getMasterPathname() const
{ 
  return _masterPathname;
}
