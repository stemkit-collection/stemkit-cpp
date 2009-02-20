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

static const sk::util::Class __class("sk::rt::thread::pthreads::Mutex");

sk::rt::thread::pthreads::Mutex::
Mutex(int mutex_type, sk::rt::Scope scope)
  : _scope(scope)
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutexattr_init(&_attributes));
  try {
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutexattr_settype(&_attributes, mutex_type));
    SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_init(&_mutex, &_attributes));
  }
  catch(...) {
    destroyMutexAttributes();
    throw;
  }
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Mutex::
makeRecursive()
{
  return new pthreads::Mutex(PTHREAD_MUTEX_RECURSIVE, sk::rt::Scope(__class.getName()));
}

#include <iostream>

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Mutex::
makeSingular()
{
  sk::rt::Scope scope(__class.getName());
  bool check = scope.getProperty("perform-error-check", sk::util::Boolean::B_TRUE);
  return new Mutex((check ? PTHREAD_MUTEX_ERRORCHECK : PTHREAD_MUTEX_NORMAL), scope);
}

sk::rt::thread::pthreads::Mutex::
~Mutex()
{
  sk::util::Exception::guard(_scope.warning(), *this, &Mutex::destroyMutex, __FUNCTION__);
  sk::util::Exception::guard(_scope.warning(), *this, &Mutex::destroyMutexAttributes, __FUNCTION__);
}

void 
sk::rt::thread::pthreads::Mutex::
destroyMutex() 
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_destroy(&_mutex));
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
  return __class;
}

void 
sk::rt::thread::pthreads::Mutex::
lock()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_lock(&_mutex));
}

void 
sk::rt::thread::pthreads::Mutex::
unlock()
{
  SK_PTHREAD_RAISE_UNLESS_SUCCESS(pthread_mutex_unlock(&_mutex));
}

bool
sk::rt::thread::pthreads::Mutex::
tryLock()
{
  return SK_PTHREAD_RAISE_UNLESS_SUCCESS_OR(EBUSY, pthread_mutex_trylock(&_mutex));
}

