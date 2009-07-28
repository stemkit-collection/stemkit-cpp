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

static const char* __className("sk::rt::thread::ScopeArbitrator");

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
  return sk::util::Class(__className);
}

void
sk::rt::thread::ScopeArbitrator::
lock()
{
  _mutex.lock();
}

bool
sk::rt::thread::ScopeArbitrator::
tryLock()
{
  return _mutex.tryLock();
}

bool
sk::rt::thread::ScopeArbitrator::
isLocked() const
{
  return _mutex.isLocked();
}

void 
sk::rt::thread::ScopeArbitrator::
unlock()
{
  _mutex.unlock();
}

void 
sk::rt::thread::ScopeArbitrator::
reset()
{
  _mutex.reset();
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
