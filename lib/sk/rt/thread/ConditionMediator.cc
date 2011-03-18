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

#include <sk/rt/thread/ConditionMediator.h>

static const sk::util::String __className("sk::rt::thread::ConditionMediator");

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
synchronize(sk::rt::thread::Conditional& block)
{
  sk::rt::thread::Generic& currentThread = sk::rt::Thread::currentThread();

  while(true) {
    lock();

    try {
      block.runEnsured(*this);
      unlock();
      break;
    }
    catch(const sk::rt::thread::ConditionMediator::WaitRequest& request) {
      unlock();

      uint64_t remaining = request.waitTime();
      bool forever = (remaining > 0 ? false : true);
      int span = 100;

      while(currentThread.isInterrupted() == false) {
        sk::rt::Thread::sleep(span);
        if(forever == false) {
          if(remaining < span) {
            throw Timeout();
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
}

void
sk::rt::thread::ConditionMediator::
unlock()
{
}

void
sk::rt::thread::ConditionMediator::
ensureLockOwner()
{
}
