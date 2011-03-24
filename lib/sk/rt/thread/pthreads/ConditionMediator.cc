/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/upcast.cxx>
#include <sk/util/Vector.cxx>

#include <sk/rt/SystemException.h>

#include "ConditionMediator.h"
#include "../ConditionTimingAdaptor.hxx"
#include "Condition.h"
#include "Mutex.h"

static const sk::util::String __className("sk::rt::thread::pthreads::ConditionMediator");

sk::rt::thread::pthreads::ConditionMediator::
ConditionMediator(const sk::rt::Scope& scope, sk::rt::Lock& lock, int capacity)
  : _scope(scope), _lock(lock)
{
  pthreads::Mutex& mutex = sk::util::upcast<pthreads::Mutex>(lock.getObject());
  for(int counter=std::max(1, capacity); counter; --counter) {
    _conditions.add(new pthreads::Condition(_scope, mutex));
  }
}

sk::rt::thread::pthreads::ConditionMediator::
~ConditionMediator()
{
}

const sk::util::Class
sk::rt::thread::pthreads::ConditionMediator::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::thread::pthreads::ConditionMediator::
invoke(bool blocking, const sk::rt::thread::Conditional& block)
{
  if(blocking == false) {
    if(_lock.tryLock() == false) {
      return false;
    }
  }
  else {
    _lock.lock();
  }

  sk::rt::thread::ConditionTimingAdaptor<pthreads::ConditionMediator> adaptor(*this);

  while(true) {
    try {
      block.process(adaptor);
      _lock.unlock();
      return true;
    }
    catch(...) {
      _lock.unlock();
      throw;
    }
  }
}

void
sk::rt::thread::pthreads::ConditionMediator::
wait(int channel)
{
  _conditions.getMutable(channel).wait();
}

void
sk::rt::thread::pthreads::ConditionMediator::
wait(int channel, const struct timespec moment)
{
  _conditions.getMutable(channel).waitUntil(moment);
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(int channel)
{
  _conditions.getMutable(channel).broadcast();
}

