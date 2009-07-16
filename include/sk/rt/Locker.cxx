/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_LOCKER_CXX_
#define _SK_RT_LOCKER_CXX_

#include <sk/rt/Locker.hxx>
#include <sk/util/Holder.cxx>

template<typename L>
sk::rt::Locker<L>::
Locker(L& lock)
  : _lockHolder(lock), _locked(true)
{
  lock.lock();
}

template<typename L>
sk::rt::Locker<L>::
~Locker()
{
  if(_lockHolder.getLinks() == 1) {
    unlock();
  }
}

template<typename L>
void
sk::rt::Locker<L>::
unlock()
{
  if(_locked == true) {
    _lockHolder.get().unlock();
    _locked = false;
  }
}

#endif /* _SK_RT_LOCKER_CXX_ */
