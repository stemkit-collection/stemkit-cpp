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
#include <sk/util/Holder.cxx>

#include <sk/rt/thread/ReentrantLock.h>
#include <sk/rt/Thread.h>

#include "Implementation.h"
#include <sstream>

static const sk::util::Class __class("sk::rt::thread::ReentrantLock");

sk::rt::thread::ReentrantLock::
ReentrantLock()
  : _holdCount(0), _mutexHolder(Implementation::instance().makeRecursiveMutex())
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
  _mutexHolder.get().lock();
  processLocked();
}

bool
sk::rt::thread::ReentrantLock::
tryLock()
{
  if(_mutexHolder.get().tryLock() == true) {
    processLocked();
    return true;
  }
  return false;
}

void
sk::rt::thread::ReentrantLock::
processLocked()
{
  if(_holdCount == 0) {
    _ownerHolder.set(sk::rt::Thread::currentThread());
  }
  ++_holdCount;
}

void
sk::rt::thread::ReentrantLock::
processUnlocked()
{
  if(_holdCount > 0) {
    --_holdCount;
  }
  if(_holdCount == 0) {
    _ownerHolder.clear();
  }
}

void
sk::rt::thread::ReentrantLock::
unlock()
{
  if(_mutexHolder.get().tryLock() == true) {
    processUnlocked();
    _mutexHolder.get().unlock();
  }
  _mutexHolder.get().unlock();
}

void
sk::rt::thread::ReentrantLock::
synchronize(const sk::rt::Runnable& block)
{
  _mutexHolder.get().lock();
  processLocked();

  try {
    block.run();
  }
  catch(...) {
    processUnlocked();
    _mutexHolder.get().unlock();
    throw;
  }
  processUnlocked();
  _mutexHolder.get().unlock();
}

bool
sk::rt::thread::ReentrantLock::
isLocked() const
{
  return getHoldCount() > 0;
}

int
sk::rt::thread::ReentrantLock::
getHoldCount() const
{
  return _holdCount;
}

const sk::util::String
sk::rt::thread::ReentrantLock::
inspect() const
{
  std::stringstream stream;
  stream << "<"
    << __class.getName() << "#" << std::hex << getId() << ": "
    << "locked=" << std::boolalpha << isLocked() << ", "
    << "count=" << _holdCount << ", "
    << "owner=" << (_ownerHolder.isEmpty() ? "?" : _ownerHolder.get().inspect())
    << ">"
  ;
  return stream.str();
}
