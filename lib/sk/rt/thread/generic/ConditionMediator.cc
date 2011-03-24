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
#include "../ConditionTimespecAdaptor.hxx"
#include <sk/rt/TimeoutException.h>
#include <sk/rt/Locker.h>

static const sk::util::String __className("sk::rt::thread::generic::ConditionMediator");

struct sk::rt::thread::generic::ConditionMediator::WaitRequest {
  WaitRequest(int number)
    : channel(number) {}

  int channel;
};

sk::rt::thread::generic::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock, int capacity)
  : _lock(lock)
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

bool
sk::rt::thread::generic::ConditionMediator::
invoke(bool blocking, const sk::rt::thread::Conditional& block)
{
  sk::rt::thread::ConditionTimespecAdaptor<generic::ConditionMediator> adaptor(*this);

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
      thread_container_t& waiters = _waiters.getMutable(request.channel);
      (sk::rt::Locker(_mutex), waiters.add(currentThread));

      _lock.unlock();

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(100);
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
  throw WaitRequest(channel);
}

void
sk::rt::thread::generic::ConditionMediator::
wait(int channel, const struct timespec moment)
{
  throw WaitRequest(channel);
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
