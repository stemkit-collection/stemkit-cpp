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

#include <sk/rt/thread/ReentrantLock.h>
#include "Implementation.h"

static const sk::util::Class __class("sk::rt::thread::ReentrantLock");

sk::rt::thread::ReentrantLock::
ReentrantLock()
  : AbstractLock(Implementation::instance().makeRecursiveMutex(), true),
    _counter(0)
{
}

sk::rt::thread::ReentrantLock::
~ReentrantLock()
{
}

const sk::util::Class
sk::rt::thread::ReentrantLock::
getClass() const
{
  return __class;
}

void
sk::rt::thread::ReentrantLock::
lock()
{
  AbstractLock::lock();
  processLocked();
}

bool
sk::rt::thread::ReentrantLock::
tryLock()
{
  if(AbstractLock::tryLock() == true) {
    processLocked();
    return true;
  }
  return false;
}

void
sk::rt::thread::ReentrantLock::
processLocked()
{
  ++_counter;
}

void
sk::rt::thread::ReentrantLock::
processUnlocked()
{
  if(_counter > 0) {
    --_counter;
  }
}

void
sk::rt::thread::ReentrantLock::
unlock()
{
  if(AbstractLock::tryLock() == true) {
    processUnlocked();
    AbstractLock::unlock();
  }
  AbstractLock::unlock();
}

bool
sk::rt::thread::ReentrantLock::
isLocked() const
{
  return _counter > 0;
}

int
sk::rt::thread::ReentrantLock::
getCounter() const
{
  return _counter;
}

void
sk::rt::thread::ReentrantLock::
collectInspectInfo(std::ostream& stream) const
{
  AbstractLock::collectInspectInfo(stream);
  stream << ", " << "count=" << _counter;
}
