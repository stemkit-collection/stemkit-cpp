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

#include <iostream>

void
sk::rt::ReentrantLock::
lock()
{
  thread::AbstractLock::lock();
  processLocked();
  std::cerr << ">>> lock(), counter=" << _counter << std::endl;
}

bool
sk::rt::ReentrantLock::
tryLock()
{
  std::cerr << ">>> tryLock(), counter=" << _counter << std::endl;
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
  std::cerr << ">>> processLocked(), counter=" << _counter << std::endl;
  ++_counter;
}

void
sk::rt::ReentrantLock::
processUnlocked()
{
  std::cerr << ">>> processUnlocked(in), counter=" << _counter << std::endl;
  if(_counter > 0) {
    --_counter;
  }
  std::cerr << ">>> processUnlocked(out), counter=" << _counter << std::endl;
}

void
sk::rt::ReentrantLock::
unlock()
{
  if(thread::AbstractLock::tryLock() == true) {
    std::cerr << ">>> tryLock() successful" << std::endl;
    processUnlocked();
    thread::AbstractLock::unlock();
  }
  else {
    std::cerr << ">>> tryLock() failed" << std::endl;
  }
  thread::AbstractLock::unlock();
  std::cerr << ">>> unlock(), counter=" << _counter << std::endl;
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
