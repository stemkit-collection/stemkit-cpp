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
#include "../ConditionAdaptor.hxx"
#include <sk/rt/TimeoutException.h>
#include <sk/rt/Locker.h>

static const sk::util::String __className("sk::rt::thread::generic::ConditionMediator");

struct sk::rt::thread::generic::ConditionMediator::WaitRequest {
  WaitRequest(int number, uint64_t milliseconds)
    : channel(number), timeout(milliseconds) {}

  uint64_t timeout;
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
  sk::rt::thread::ConditionAdaptor<generic::ConditionMediator> adaptor(*this);

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

      uint64_t remaining = request.timeout;
      bool forever = (remaining > 0 ? false : true);
      uint64_t span = 100;

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(span);
        if(forever == false) {
          if(remaining < span) {
            (sk::rt::Locker(_mutex), waiters.remove(currentThread));
            throw sk::rt::TimeoutException();
          }
          remaining -= span;
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
wait(int channel, uint64_t timeout)
{
  throw WaitRequest(channel, timeout);
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