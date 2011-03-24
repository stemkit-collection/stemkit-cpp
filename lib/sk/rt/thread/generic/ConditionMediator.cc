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
#include <sk/util/ArrayList.cxx>
#include <sk/util/Vector.cxx>

#include "ConditionMediator.h"
#include "../ConditionTimingAdaptor.hxx"
#include <sk/rt/TimeoutException.h>
#include <sk/rt/Locker.h>

static const sk::util::String __className("sk::rt::thread::generic::ConditionMediator");

sk::rt::thread::generic::ConditionMediator::
ConditionMediator(const sk::rt::Scope& scope, sk::rt::Lock& lock, int capacity)
  : _scope(scope), _lock(lock), _delay(std::max(1, scope.getProperty("generic-condition-mediator-delay", 100)))
{
  for(int counter=std::max(1, capacity); counter; --counter) {
    _waiters.add(new thread_container_t);
  }
}

sk::rt::thread::generic::ConditionMediator::
~ConditionMediator()
{
}

const sk::util::Class
sk::rt::thread::generic::ConditionMediator::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct WaitRequest {};
}

bool
sk::rt::thread::generic::ConditionMediator::
invoke(bool blocking, const sk::rt::thread::Conditional& block)
{
  sk::rt::thread::ConditionTimingAdaptor<generic::ConditionMediator> adaptor(*this);

  while(true) {
    if(blocking == false) {
      if(_lock.tryLock() == false) {
        return false;
      }
      blocking = true;
    }
    else {
      _lock.lock();
    }

    try {
      block.process(adaptor);
      _lock.unlock();
      return true;
    }
    catch(const WaitRequest& request) {
      thread::Generic& currentThread = sk::rt::Thread::currentThread();
      thread_container_t& waiters = _waiters.getMutable(adaptor.getChannel());
      (sk::rt::Locker(_mutex), waiters.add(currentThread));

      _lock.unlock();

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(_delay);
        if(adaptor.isMomentReached() == true) {
          (sk::rt::Locker(_mutex), waiters.remove(currentThread));
          throw sk::rt::TimeoutException();
        }
      }
    }
    catch(...) {
      _lock.unlock();
      throw;
    }
  }
}

void
sk::rt::thread::generic::ConditionMediator::
wait(int channel)
{
  throw WaitRequest();
}

void
sk::rt::thread::generic::ConditionMediator::
wait(int channel, const sk::rt::Time& moment)
{
  throw WaitRequest();
}

void
sk::rt::thread::generic::ConditionMediator::
announce(int channel)
{
  struct Interruptor : public virtual sk::util::Processor<sk::rt::thread::Generic> {
    void process(sk::rt::thread::Generic& thread) const {
      thread.interrupt();
    }
  };
  thread_container_t& waiters = _waiters.getMutable(channel);
  sk::rt::Locker locker(_mutex);

  waiters.forEach(Interruptor());
  waiters.clear();
}
