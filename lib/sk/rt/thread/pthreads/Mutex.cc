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
#include <iostream>

static const sk::util::Class __class("sk::rt::thread::pthreads::Mutex");

namespace {
  void exceptionUnlessSuccess(const char* name, int status) {
    if(status != 0) {
      throw sk::util::SystemException("pthread_" + sk::util::String(name) + "()", status);
    }
  }
}

sk::rt::thread::pthreads::Mutex::
Mutex()
{
  exceptionUnlessSuccess("mutexattr_init", pthread_mutexattr_init(&_attributes));
  try {
    exceptionUnlessSuccess("mutexattr_settype", pthread_mutexattr_settype(&_attributes, PTHREAD_MUTEX_RECURSIVE));
    exceptionUnlessSuccess("mutex_init", pthread_mutex_init(&_mutex, &_attributes));
  }
  catch(...) {
    pthread_mutexattr_destroy(&_attributes);
    throw;
  }
}

sk::rt::thread::pthreads::Mutex::
~Mutex()
{
  try {
    exceptionUnlessSuccess("mutex_destroy", pthread_mutex_destroy(&_mutex));
  }
  catch(const std::exception& exception) {
    std::cerr << "[" << SK_METHOD << "] " << exception.what() << std::endl;
  }

  try {
    exceptionUnlessSuccess("mutexattr_destroy", pthread_mutexattr_destroy(&_attributes));
  }
  catch(const std::exception& exception) {
    std::cerr << "[" << SK_METHOD << "] " << exception.what() << std::endl;
  }
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
  exceptionUnlessSuccess("mutex_trylock", pthread_mutex_trylock(&_mutex));
  return true;
}

