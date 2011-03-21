/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/rt/TimeoutException.h>

#include "Condition.h"
#include "Exception.h"

#include <errno.h>

static const sk::util::String __className("sk::rt::thread::pthreads::Condition");

sk::rt::thread::pthreads::Condition::
Condition(const sk::rt::Scope& scope, pthreads::Mutex& mutex)
  : _scope(scope), _mutexHandle(mutex.getHandle())
{
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cond_init(&_conditionHandle, 0));
}

sk::rt::thread::pthreads::Condition::
~Condition()
{
  sk::util::Exception::guard(_scope.warning(), *this, &Condition::cleanup, __FUNCTION__);
}

void
sk::rt::thread::pthreads::Condition::
cleanup()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cond_destroy(&_conditionHandle));
}

const sk::util::Class
sk::rt::thread::pthreads::Condition::
getClass() const
{
  return sk::util::Class(__className);
}

pthread_cond_t&
sk::rt::thread::pthreads::Condition::
getHandle()
{
  return _conditionHandle;
}

void
sk::rt::thread::pthreads::Condition::
waitUntil(const struct timespec& moment)
{
  if(SK_PTHREAD_RAISE_UNLESS_SUCCESS_OR(ETIMEDOUT, pthread_cond_timedwait(&_conditionHandle, &_mutexHandle, &moment)) == false) {
    throw sk::rt::TimeoutException(SK_METHOD);
  }
}

void
sk::rt::thread::pthreads::Condition::
wait()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cond_wait(&_conditionHandle, &_mutexHandle));
}

void
sk::rt::thread::pthreads::Condition::
broadcast()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cond_broadcast(&_conditionHandle));
}

void
sk::rt::thread::pthreads::Condition::
signal()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_cond_signal(&_conditionHandle));
}
