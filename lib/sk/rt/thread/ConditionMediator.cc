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
#include <sk/util/IllegalStateException.h>
#include <sk/util/ArrayList.cxx>

#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/TimeoutException.h>
#include <sk/rt/Locker.h>

static const sk::util::String __className("sk::rt::thread::ConditionMediator");

struct sk::rt::thread::ConditionMediator::WaitRequest : public virtual sk::util::Object {
  WaitRequest(uint64_t milliseconds)
    : _milliseconds(milliseconds) {}

  uint64_t waitMilliseconds() const {
    return _milliseconds;
  }
  uint64_t _milliseconds;
};

sk::rt::thread::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock)
  : _lock(lock)
{
}

sk::rt::thread::ConditionMediator::
~ConditionMediator()
{
}

const sk::util::Class
sk::rt::thread::ConditionMediator::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::thread::ConditionMediator::
invoke(const sk::rt::thread::Conditional& block)
{
  while(true) {
    _lock.lock();

    try {
      block.process(*this);
      _lock.unlock();
      break;
    }
    catch(const sk::rt::thread::ConditionMediator::WaitRequest& request) {
      sk::rt::thread::Generic& currentThread = sk::rt::Thread::currentThread();
      (sk::rt::Locker(_mutex), _waiters.add(currentThread));

      _lock.unlock();

      uint64_t remaining = request.waitMilliseconds();
      bool forever = (remaining > 0 ? false : true);
      uint64_t span = 100;

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(span);
        if(forever == false) {
          if(remaining < span) {
            (sk::rt::Locker(_mutex), _waiters.remove(currentThread));
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
sk::rt::thread::ConditionMediator::
ensure(bool expression, uint64_t timeout)
{
  if(expression == false) {
    throw WaitRequest(timeout);
  }
}

void
sk::rt::thread::ConditionMediator::
announce(bool expression)
{
  if(expression == false) {
    return;
  }
  sk::rt::Locker locker(_mutex);

  struct Interruptor : public virtual sk::util::Processor<sk::rt::thread::Generic> {
    void process(sk::rt::thread::Generic& thread) const {
      thread.interrupt();
    }
  };
  _waiters.forEach(Interruptor());
  _waiters.clear();
}
