/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/rt/Locker.h>
#include <sk/util/Holder.cxx>

sk::rt::Locker::
Locker(sk::rt::Lock& lock)
  : _lockHolder(lock), _locked(true)
{
  lock.lock();
}

sk::rt::Locker::
~Locker()
{
  if(_lockHolder.getLinks() == 1) {
    unlock();
  }
}

void
sk::rt::Locker::
unlock()
{
  if(_locked == true) {
    _lockHolder.getMutable().unlock();
    _locked = false;
  }
}

