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

#include <sk/rt/thread/ScopeArbitrator.h>
#include <sk/rt/Thread.h>

static const sk::util::Class __class("sk::rt::thread::ScopeArbitrator");

sk::rt::thread::ScopeArbitrator::
ScopeArbitrator()
  : _mutex(false)
{
}

sk::rt::thread::ScopeArbitrator::
~ScopeArbitrator()
{
}

const sk::util::Class
sk::rt::thread::ScopeArbitrator::
getClass() const
{
  return __class;
}

void
sk::rt::thread::ScopeArbitrator::
lock()
{
  _mutex.lock();
}

void 
sk::rt::thread::ScopeArbitrator::
unlock()
{
  _mutex.unlock();
}

uint64_t
sk::rt::thread::ScopeArbitrator::
currentThreadId() const
{
  if(sk::rt::Thread::isReady() == false) {
    return 0;
  }
  return sk::rt::Thread::currentThread().getId();
}
