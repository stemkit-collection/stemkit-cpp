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

#include <sk/rt/thread/AbstractLock.h>
#include "Implementation.h"

#include <sstream>

static const sk::util::Class __class("sk::rt::thread::AbstractLock");

sk::rt::thread::AbstractLock::
AbstractLock(abstract::Mutex* mutex)
  : _mutexHolder(mutex)
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
}

bool
sk::rt::thread::AbstractLock::
tryLock()
{
  return _mutexHolder.get().tryLock();
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
isLocked() const
{
  if(_mutexHolder.get().tryLock() == true) {
    _mutexHolder.get().unlock();
    return false;
  }
  return true;
}

const sk::util::String
sk::rt::thread::AbstractLock::
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
