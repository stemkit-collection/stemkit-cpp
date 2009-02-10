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
#include <sk/util/Method.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Boolean.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/thread/Mutex.h>
#include <sk/rt/Thread.h>

#include "Dispatcher.h"
#include "Implementation.h"

#include <sstream>

static const sk::util::Class __class("sk::rt::thread::Mutex");

sk::rt::thread::Mutex::
Mutex()
  : _scope(*this), _locked(false), _holdCount(0), _mutexHolder(Implementation::instance().makeMutex())
{
  _maintainOwner = _scope.getProperty("maintain-owner", sk::util::Boolean::B_FALSE);
  _maintainState = _scope.getProperty("maintain-state", sk::util::Boolean::B_FALSE);
}

sk::rt::thread::Mutex::
~Mutex()
{
}

const sk::util::Class
sk::rt::thread::Mutex::
getClass() const
{
  return __class;
}

void
sk::rt::thread::Mutex::
lock()
{
  _mutexHolder.get().lock();
  processLocked();
}

bool
sk::rt::thread::Mutex::
tryLock()
{
  if(_mutexHolder.get().tryLock() == true) {
    processLocked();
    return true;
  }
  return false;
}

void
sk::rt::thread::Mutex::
processLocked()
{
  if(_maintainState == true) {
    _locked = true;
    ++_holdCount;

    if(_maintainOwner) {
      _ownerHolder.set(sk::rt::Thread::currentThread());
    }
  }
}

void
sk::rt::thread::Mutex::
processUnlocked()
{
  if(_maintainState == true) {
    if(_holdCount > 0) {
      --_holdCount;
    }
    if(_holdCount == 0) {
      _ownerHolder.clear();
      _locked = false;
      _holdCount = 0;
    }
  }
}

void
sk::rt::thread::Mutex::
unlock()
{
  if(_maintainState == true) {
    if(_mutexHolder.get().tryLock() == true) {
      processUnlocked();
      _mutexHolder.get().unlock();
    }
  }
  _mutexHolder.get().unlock();
}

void
sk::rt::thread::Mutex::
synchronize(const sk::rt::Runnable& block)
{
  _mutexHolder.get().lock();
  processLocked();

  try {
    block.run();
  }
  catch(...) {
    processUnlocked();
    unlock();
    throw;
  }
  processUnlocked();
  unlock();
}

bool
sk::rt::thread::Mutex::
isLocked() const
{
  if(_maintainState == true) {
    return _locked;
  }
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int
sk::rt::thread::Mutex::
getHoldCount() const
{
  if(_maintainState == true) {
    return _holdCount;
  }
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::rt::thread::Mutex::
inspect() const
{
  std::stringstream stream;
  stream << "<"
    << __class.getName() << ":" << std::hex << getId() << ": "
    << "lock=" << (_maintainState==false ? "?" : (_locked ? "on" : "off")) << ", "
    << "count=" << (_maintainState==false ? "?" : sk::util::Integer::toString(_holdCount)) << ", "
    << "owner=" << (_ownerHolder.isEmpty() ? "?" : _ownerHolder.get().inspect())
    << ">"
  ;
  return stream.str();
}
