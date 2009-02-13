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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/SystemException.h>

#include "Implementation.h"
#include <pthread.h>

static sk::util::Class __class("sk::rt::thread::pthreads::Implementation");

namespace {
  void exceptionUnlessSuccess(const char* name, int status) {
    if(status != 0) {
      throw sk::util::SystemException("pthread_" + sk::util::String(name) + "()", status);
    }
  }
}

sk::rt::thread::pthreads::Implementation::
Implementation()
{
  exceptionUnlessSuccess("key_create", pthread_key_create(&_currentThreadKey, 0));
}

sk::rt::thread::pthreads::Implementation::
~Implementation()
{
  pthread_key_delete(_currentThreadKey);
}

const sk::util::Class
sk::rt::thread::pthreads::Implementation::
getClass() const
{
  return __class;
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Implementation::
makeSimpleMutex() const
{
#ifndef PTHREAD_MUTEX_ERRORCHECK
  throw sk::util::UnsupportedOperationException(SK_METHOD);
#else
  return new pthreads::Mutex(PTHREAD_MUTEX_ERRORCHECK);
#endif
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Implementation::
makeRecursiveMutex() const
{
#ifndef PTHREAD_MUTEX_RECURSIVE
  throw sk::util::UnsupportedOperationException(SK_METHOD);
#else
  return new pthreads::Mutex(PTHREAD_MUTEX_RECURSIVE);
#endif
}

sk::rt::thread::pthreads::Thread*
sk::rt::thread::pthreads::Implementation::
makeThread(sk::rt::Runnable& target, sk::rt::thread::Generic& handle) const
{
  return new pthreads::Thread(*this, target, handle);
}

sk::rt::thread::pthreads::Thread*
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
  exceptionUnlessSuccess("setspecific", pthread_setspecific(_currentThreadKey, &handle));
}

void
sk::rt::thread::pthreads::Implementation::
clearGeneric() const
{
  exceptionUnlessSuccess("setspecific", pthread_setspecific(_currentThreadKey, 0));
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
