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

#include <sk/rt/Thread.h>
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/TimeoutException.h>

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
  : _lock(lock), _locked(false)
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
synchronize(sk::rt::thread::Conditional& block)
{
  while(true) {
    lock();

    try {
      block.runEnsured(*this);
      unlock();
      break;
    }
    catch(const sk::rt::thread::ConditionMediator::WaitRequest& request) {
      unlock();

      sk::rt::thread::Generic& currentThread = sk::rt::Thread::currentThread();
      uint64_t remaining = request.waitMilliseconds();
      bool forever = (remaining > 0 ? false : true);
      uint64_t span = 100;

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(span);
        if(forever == false) {
          if(remaining < span) {
            throw sk::rt::TimeoutException();
          }
          remaining -= span;
        }
      }
    }
    catch(...) {
      unlock();
      throw;
    }
  }
}

void
sk::rt::thread::ConditionMediator::
ensure(bool expression, int timeout)
{
  ensureLockOwner();
}

void
sk::rt::thread::ConditionMediator::
announce()
{
  ensureLockOwner();
}

void
sk::rt::thread::ConditionMediator::
lock()
{
  _lock.lock();
  _locked = true;
  _lockOwnerId = sk::rt::Thread::currentThread().getId();
}

void
sk::rt::thread::ConditionMediator::
unlock()
{
  _locked = false;
  _lock.unlock();
}

void
sk::rt::thread::ConditionMediator::
ensureLockOwner()
{
  if(!_locked || _lockOwnerId != sk::rt::Thread::currentThread().getId()) {
    throw sk::util::IllegalStateException("Not a lock owner");
  }
}
