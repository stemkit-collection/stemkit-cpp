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
      throw sk::util::SystemException("pthread_mutex_" + sk::util::String(name) + "()", status);
    }
  }
}

sk::rt::thread::pthreads::Mutex::
Mutex()
{
  exceptionUnlessSuccess("init", pthread_mutex_init(&_mutex, 0));
}

sk::rt::thread::pthreads::Mutex::
~Mutex()
{
  try {
    exceptionUnlessSuccess("destroy", pthread_mutex_destroy(&_mutex));
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
  exceptionUnlessSuccess("lock", pthread_mutex_lock(&_mutex));
}

void 
sk::rt::thread::pthreads::Mutex::
unlock()
{
  exceptionUnlessSuccess("unlock", pthread_mutex_unlock(&_mutex));
}

