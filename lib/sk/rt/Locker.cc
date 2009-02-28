/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/Locker.h>

static const sk::util::Class __class("sk::rt::Locker");

sk::rt::Locker::
Locker(sk::rt::Lock& lock)
  : _lockHolder(lock)
{
  _lockHolder.get().lock();
}

sk::rt::Locker::
~Locker()
{
  if(_lockHolder.getLinks() == 1) {
    _lockHolder.get().unlock();
  }
}

const sk::util::Class
sk::rt::Locker::
getClass() const
{
  return __class;
}
