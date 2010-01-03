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

static const char* __className("sk::rt::thread::AbstractLock");

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
  return sk::util::Class(__className);
}

void
sk::rt::thread::AbstractLock::
lock()
{
  _mutexHolder.getMutable().lock();
  registerOwnership();
}

void 
sk::rt::thread::AbstractLock::
registerOwnership()
{
  if(_ownership == true) {
    _lastOwner = sk::rt::Thread::currentThread().getId();
  }
}

bool
sk::rt::thread::AbstractLock::
tryLock()
{
  if(_mutexHolder.getMutable().tryLock() == true) {
    registerOwnership();
    return true;
  }
  return false;
}

void
sk::rt::thread::AbstractLock::
unlock()
{
  _mutexHolder.getMutable().unlock();
}

void
sk::rt::thread::AbstractLock::
reset()
{
  _mutexHolder.getMutable().reset();
}

bool
sk::rt::thread::AbstractLock::
tryLockCheck() const
{
  if(_mutexHolder.getMutable().tryLock() == true) {
    _mutexHolder.getMutable().unlock();
    return false;
  }
  return true;
}

void
sk::rt::thread::AbstractLock::
collectInspectInfo(std::ostream& stream) const
{
  stream << "owner=" ;
  if(_ownership == true) {
    stream << std::hex << _lastOwner;
  }
  else {
    stream << '?';
  }
  stream  << ", " << "locked=" << std::boolalpha << isLocked();
}

const sk::util::String
sk::rt::thread::AbstractLock::
inspect() const
{
  std::ostringstream stream;
  stream << "<" << getClass().getName() << "#" << std::hex << getId() << ": ";
  collectInspectInfo(stream);
  stream << ">";

  return stream.str();
}
