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

#include <sk/rt/thread/Mutex.h>
#include "Implementation.h"

#include <sstream>

static const sk::util::Class __class("sk::rt::thread::Mutex");

sk::rt::thread::Mutex::
Mutex()
  : _mutexHolder(Implementation::instance().makeSimpleMutex())
{
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
}

bool
sk::rt::thread::Mutex::
tryLock()
{
  return _mutexHolder.get().tryLock();
}

void
sk::rt::thread::Mutex::
unlock()
{
  _mutexHolder.get().unlock();
}

void
sk::rt::thread::Mutex::
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
sk::rt::thread::Mutex::
isLocked() const
{
  if(_mutexHolder.get().tryLock() == true) {
    _mutexHolder.get().unlock();
    return false;
  }
  return true;
}

const sk::util::String
sk::rt::thread::Mutex::
inspect() const
{
  std::stringstream stream;
  stream << "<"
    << __class.getName() << ":" << std::hex << getId() << ": "
    << "locked?=" << std::boolalpha << isLocked() 
    << ">"
  ;
  return stream.str();
}
