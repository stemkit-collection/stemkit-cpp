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

#include <sk/rt/Thread.h>
#include <sk/rt/thread/AbstractLock.h>
#include "Implementation.h"

#include <sstream>

static const sk::util::Class __class("sk::rt::thread::AbstractLock");

sk::rt::thread::AbstractLock::
AbstractLock(abstract::Mutex* mutex, bool ownership)
  : _mutexHolder(mutex), _lastOwner(0), _ownership(ownership)
{
}

sk::rt::thread::AbstractLock::
~AbstractLock()
{
}

const sk::util::Class
sk::rt::thread::AbstractLock::
getClass() const
{
  return __class;
}

void
sk::rt::thread::AbstractLock::
lock()
{
  _mutexHolder.get().lock();
  if(_ownership == true) {
    _lastOwner = sk::rt::Thread::currentThread().getId();
  }
}

bool
sk::rt::thread::AbstractLock::
tryLock()
{
  if(_mutexHolder.get().tryLock() == true) {
    // _lastOwner = sk::rt::Thread::currentThread().getId();
    return true;
  }
  return false;
}

void
sk::rt::thread::AbstractLock::
unlock()
{
  _mutexHolder.get().unlock();
}

void
sk::rt::thread::AbstractLock::
synchronize(const sk::rt::Runnable& block)
{
  lock();

  try {
    block.run();
  }
  catch(...) {
    unlock();
    throw;
  }
  unlock();
}

bool
sk::rt::thread::AbstractLock::
tryLockCheck() const
{
  if(_mutexHolder.get().tryLock() == true) {
    _mutexHolder.get().unlock();
    return false;
  }
  return true;
}

void
sk::rt::thread::AbstractLock::
collectInspectInfo(std::ostream& stream) const
{
  stream 
    << "owner=" << std::hex << _lastOwner << ", "
    << "locked=" << std::boolalpha << isLocked()
  ;
}

const sk::util::String
sk::rt::thread::AbstractLock::
inspect() const
{
  std::stringstream stream;
  stream << "<" << getClass().getName() << "#" << std::hex << getId() << ": ";
  collectInspectInfo(stream);
  stream << ">";

  return stream.str();
}
