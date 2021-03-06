/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include "Mutex.h"
#include "Exception.h"
#include <errno.h>

static const char* __className("sk::rt::thread::pthreads::Mutex");

sk::rt::thread::pthreads::Mutex::
Mutex(int mutex_type, const sk::rt::Scope& scope)
  : _scope(scope)
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutexattr_init(&_attributes));
  try {
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutexattr_settype(&_attributes, mutex_type));
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_init(&_mutexHandle, &_attributes));
  }
  catch(...) {
    destroyMutexAttributes();
    throw;
  }
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Mutex::
makeRecursive(const sk::rt::Scope& scope)
{
  return new pthreads::Mutex(PTHREAD_MUTEX_RECURSIVE, scope);
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Mutex::
makeSingular(const sk::rt::Scope& scope)
{
  bool check = scope.getProperty("mutex-error-check", sk::util::Boolean::B_TRUE);
  return new Mutex((check ? PTHREAD_MUTEX_ERRORCHECK : PTHREAD_MUTEX_NORMAL), scope);
}

sk::rt::thread::pthreads::Mutex::
~Mutex()
{
  sk::util::Exception::guard(_scope.warning(), *this, &Mutex::destroyMutex, __FUNCTION__);
  sk::util::Exception::guard(_scope.warning(), *this, &Mutex::destroyMutexAttributes, __FUNCTION__);
}

pthread_mutex_t&
sk::rt::thread::pthreads::Mutex::
getHandle()
{
  return _mutexHandle;
}

void
sk::rt::thread::pthreads::Mutex::
destroyMutex()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_destroy(&_mutexHandle));
}

void
sk::rt::thread::pthreads::Mutex::
destroyMutexAttributes()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutexattr_destroy(&_attributes));
}

const sk::util::Class
sk::rt::thread::pthreads::Mutex::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::thread::pthreads::Mutex::
lock()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_lock(&_mutexHandle));
}

void
sk::rt::thread::pthreads::Mutex::
unlock()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_unlock(&_mutexHandle));
}

void
sk::rt::thread::pthreads::Mutex::
reset()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_init(&_mutexHandle, &_attributes));
}

bool
sk::rt::thread::pthreads::Mutex::
tryLock()
{
  // 2010-04-28 ATTENTION: pthread_mutex_trylock() is broken under MKS Toolkit
  // on Windows - on recursive locks it returns EDEADLK on all invocations
  // with the mutex already locked by the current thread.
  //
  return SK_PTHREAD_RAISE_UNLESS_SUCCESS_OR(sk::util::Integers() << EBUSY << EDEADLK, pthread_mutex_trylock(&_mutexHandle));
}

bool
sk::rt::thread::pthreads::Mutex::
hasEnterCount() const
{
  return false;
}

int
sk::rt::thread::pthreads::Mutex::
getEnterCount() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
