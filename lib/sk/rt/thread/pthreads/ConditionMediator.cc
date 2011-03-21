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
#include "Condition.h"
#include "Mutex.h"

#include <sys/time.h>

static const sk::util::String __className("sk::rt::thread::pthreads::ConditionMediator");

struct sk::rt::thread::pthreads::ConditionMediator::WaitRequest {
  WaitRequest(int number, uint64_t milliseconds)
    : channel(number), timeout(milliseconds) {}

  uint64_t timeout;
  int channel;
};

sk::rt::thread::pthreads::ConditionMediator::
ConditionMediator(sk::rt::Lock& lock, int capacity)
  : _lock(lock)
{
  pthreads::Mutex& mutex = sk::util::upcast<pthreads::Mutex>(lock.getObject());
  for(int counter=std::min(1, capacity); counter; --counter) {
    _conditions.add(new pthreads::Condition(mutex));
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

void
sk::rt::thread::pthreads::ConditionMediator::
invoke(const sk::rt::thread::Conditional& block)
{
  _lock.lock();

  bool momentCalculated = false;
  struct timespec moment;

  while(true) {
    try {
      try {
        block.process(*this);
        _lock.unlock();
        return;
      }
      catch(const WaitRequest& request) {
        pthreads::Condition& condition = _conditions.getMutable(request.channel);
        if(request.timeout) {
          if(momentCalculated == false) {
            struct timeval now;
            if(gettimeofday(&now, 0) < 0) {
              throw sk::rt::SystemException("gettimeofday");
            }
            moment.tv_sec = now.tv_sec + (request.timeout / 1000);
            moment.tv_nsec = (now.tv_usec + ((request.timeout % 1000) * 1000)) * 1000;
            momentCalculated = true;
          }
          condition.waitUntil(moment);
        }
        else {
          condition.wait();
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
sk::rt::thread::pthreads::ConditionMediator::
ensure(bool expression, uint64_t timeout)
{
  ensure(0, expression, timeout);
}

void
sk::rt::thread::pthreads::ConditionMediator::
ensure(int channel, bool expression, uint64_t timeout)
{
  if(expression == false) {
    throw WaitRequest(channel, timeout);
  }
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(bool expression)
{
  announce(0, expression);
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(int channel, bool expression)
{
  if(expression == false) {
    return;
  }
  _conditions.getMutable(channel).broadcast();
}

