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
#include <sk/util/SystemException.h>

#include "Mutex.h"

static const sk::util::Class __class("sk::rt::thread::pthreads::Mutex");

namespace {
  void exceptionUnlessSuccess(const char* name, int status) {
    if(status != 0) {
      throw sk::util::SystemException("pthread_" + sk::util::String(name) + "()", status);
    }
  }
}

sk::rt::thread::pthreads::Mutex::
Mutex(int mutex_type)
  : _scope(__class.getName())
{
  exceptionUnlessSuccess("mutexattr_init", pthread_mutexattr_init(&_attributes));
  try {
    exceptionUnlessSuccess("mutexattr_settype", pthread_mutexattr_settype(&_attributes, mutex_type));
    exceptionUnlessSuccess("mutex_init", pthread_mutex_init(&_mutex, &_attributes));
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
  return new pthreads::Mutex(PTHREAD_MUTEX_RECURSIVE);
}

sk::rt::thread::pthreads::Mutex*
sk::rt::thread::pthreads::Mutex::
makeSingular()
{
  return new Mutex(PTHREAD_MUTEX_ERRORCHECK);
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
  exceptionUnlessSuccess("mutex_destroy", pthread_mutex_destroy(&_mutex));
}

void 
sk::rt::thread::pthreads::Mutex::
destroyMutexAttributes() 
{
  exceptionUnlessSuccess("mutexattr_destroy", pthread_mutexattr_destroy(&_attributes));
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
  exceptionUnlessSuccess("mutex_lock", pthread_mutex_lock(&_mutex));
}

void 
sk::rt::thread::pthreads::Mutex::
unlock()
{
  exceptionUnlessSuccess("mutex_unlock", pthread_mutex_unlock(&_mutex));
}

bool
sk::rt::thread::pthreads::Mutex::
tryLock()
{
  int status = pthread_mutex_trylock(&_mutex);
  if(status == EBUSY) {
    return false;
  }
  exceptionUnlessSuccess("mutex_trylock", status);
  return true;
}

