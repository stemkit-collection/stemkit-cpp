/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IllegalStateException.h>

#include "../pthreads/ConditionMediator.h"
#include "../generic/ConditionMediator.h"

#include "Implementation.h"
#include "Exception.h"

#include <time.h>
#include <pthread.h>
#include <errno.h>

static const char* __className("sk::rt::thread::pthreads::Implementation");

sk::rt::thread::pthreads::Implementation::
Implementation()
  : _scope(__className)
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_key_create(&_currentThreadKey, 0));
}

sk::rt::thread::pthreads::Implementation::
~Implementation()
{
  sk::util::Exception::guard(_scope.warning(__FUNCTION__), *this, &Implementation::cleanup);
}

void
sk::rt::thread::pthreads::Implementation::
cleanup()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_key_delete(_currentThreadKey));
}

const sk::util::Class
sk::rt::thread::pthreads::Implementation::
getClass() const
{
  return sk::util::Class(__className);
}

sk::rt::thread::platform::ConditionMediator*
sk::rt::thread::pthreads::Implementation::
makeConditionMediator(sk::rt::Lock& lock, int capacity) const
{
  if(_scope.getProperty("generic-condition-mediator", sk::util::Boolean::B_FALSE) == true) {
    return new generic::ConditionMediator(lock, capacity);
  }
  return new pthreads::ConditionMediator(lock, capacity);
}

sk::rt::thread::platform::Mutex*
sk::rt::thread::pthreads::Implementation::
makeSimpleMutex() const
{
  return pthreads::Mutex::makeSingular();
}

sk::rt::thread::platform::Mutex*
sk::rt::thread::pthreads::Implementation::
makeRecursiveMutex() const
{
  return pthreads::Mutex::makeRecursive();
}

sk::rt::thread::platform::Thread*
sk::rt::thread::pthreads::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  return new pthreads::Thread(*this, target, handle);
}

sk::rt::thread::platform::Thread*
sk::rt::thread::pthreads::Implementation::
wrapCurrentThread(sk::rt::thread::Generic& handle) const
{
  return new pthreads::Thread(*this, handle);
}

void
sk::rt::thread::pthreads::Implementation::
installGeneric(sk::rt::thread::Generic& handle) const
{
  void* value = pthread_getspecific(_currentThreadKey);
  if(value != 0) {
    throw sk::util::IllegalStateException("Generic is already initialized for this thread");
  }
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_setspecific(_currentThreadKey, &handle));
}

void
sk::rt::thread::pthreads::Implementation::
clearGeneric() const
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_setspecific(_currentThreadKey, 0));
}

sk::rt::thread::Generic& 
sk::rt::thread::pthreads::Implementation::
getGeneric() const
{
  void* value = pthread_getspecific(_currentThreadKey);
  if(value == 0) {
    throw sk::util::IllegalStateException("Generic not initialized for this thread");
  }
  return *static_cast<sk::rt::thread::Generic*>(value);
}

void
sk::rt::thread::pthreads::Implementation::
sleep(uint64_t milliseconds) const
{
  timespec remaining;

  remaining.tv_sec = (milliseconds / 1000);
  remaining.tv_nsec = (milliseconds % 1000) * 1000000;

  while(true) {
    timespec spec = remaining;
    if(nanosleep(&spec, &remaining) < 0) {
      if(errno == EINTR) {
        continue;
      }
    }
    break;
  }
}

void
sk::rt::thread::pthreads::Implementation::
yield() const
{
  SK_RT_SYSTEM_RAISE_UNLESS_SUCCESS(sched_yield());
}
