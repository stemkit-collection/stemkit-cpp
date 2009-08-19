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

#include <sk/rt/ReentrantLock.h>
#include "thread/Implementation.h"

static const char* __className("sk::rt::ReentrantLock");

sk::rt::ReentrantLock::
ReentrantLock()
  : thread::AbstractLock(thread::Implementation::instance().makeRecursiveMutex(), true),
    _counter(0)
{
}

sk::rt::ReentrantLock::
ReentrantLock(bool ownership)
  : thread::AbstractLock(thread::Implementation::instance().makeRecursiveMutex(), ownership),
    _counter(0)
{
}

sk::rt::ReentrantLock::
~ReentrantLock()
{
}

const sk::util::Class
sk::rt::ReentrantLock::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::ReentrantLock::
lock()
{
  thread::AbstractLock::lock();
  processLocked();
}

bool
sk::rt::ReentrantLock::
tryLock()
{
  if(thread::AbstractLock::tryLock() == true) {
    processLocked();
    return true;
  }
  return false;
}

void
sk::rt::ReentrantLock::
processLocked()
{
  ++_counter;
}

void
sk::rt::ReentrantLock::
processUnlocked()
{
  if(_counter > 0) {
    --_counter;
  }
}

void
sk::rt::ReentrantLock::
unlock()
{
  if(thread::AbstractLock::tryLock() == true) {
    processUnlocked();
    thread::AbstractLock::unlock();
  }
  thread::AbstractLock::unlock();
}

bool
sk::rt::ReentrantLock::
isLocked() const
{
  return _counter > 0;
}

int
sk::rt::ReentrantLock::
getCounter() const
{
  return _counter;
}

void
sk::rt::ReentrantLock::
collectInspectInfo(std::ostream& stream) const
{
  thread::AbstractLock::collectInspectInfo(stream);
  stream << ", " << "count=" << _counter;
}
