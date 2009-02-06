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

#include "Mutex.h"

static const sk::util::Class __class("sk::rt::thread::pthreads::Mutex");

sk::rt::thread::pthreads::Mutex::
Mutex()
{
  int rc = pthread_mutex_init(&_mutex, 0);
}

sk::rt::thread::pthreads::Mutex::
~Mutex()
{
  pthread_mutex_destroy(&_mutex);
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
  pthread_mutex_lock(&_mutex);
}

void 
sk::rt::thread::pthreads::Mutex::
unlock()
{
  pthread_mutex_unlock(&_mutex);
}
