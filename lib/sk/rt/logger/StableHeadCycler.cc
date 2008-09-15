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

#include "StableHeadCycler.h"

sk::rt::logger::StableHeadCycler::
StableHeadCycler()
{
}

sk::rt::logger::StableHeadCycler::
~StableHeadCycler()
{
}

const sk::util::Class
sk::rt::logger::StableHeadCycler::
getClass() const
{
  return sk::util::Class("sk::rt::logger::StableHeadCycler");
}

sk::rt::logger::StableHeadCycler*
sk::rt::logger::StableHeadCycler::
clone() const
{
  return new StableHeadCycler(*this);
}
