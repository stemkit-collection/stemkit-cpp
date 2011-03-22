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
#include "../ConditionAdaptor.hxx"
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
  _lock.lock();

  sk::rt::thread::ConditionAdaptor<pthreads::ConditionMediator> adaptor(*this);
  bool momentCalculated = false;
  struct timespec moment;

  while(true) {
    try {
      try {
        block.process(adaptor);
        _lock.unlock();
        return true;
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
wait(int channel, uint64_t timeout)
{
  throw WaitRequest(channel, timeout);
}

void
sk::rt::thread::pthreads::ConditionMediator::
announce(int channel)
{
  _conditions.getMutable(channel).broadcast();
}

