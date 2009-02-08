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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/thread/Mutex.h>
#include <sk/rt/thread/abstract/Factory.h>

#include "Dispatcher.h"
#include "Implementation.h"

static const sk::util::Class __class("sk::rt::thread::Mutex");

sk::rt::thread::Mutex::
Mutex()
  : _locked(false), _mutexHolder(Implementation::instance().makeMutex())
{
}

sk::rt::thread::Mutex::
~Mutex()
{
  _locked = false;
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
  _locked = true;
}

void
sk::rt::thread::Mutex::
unlock()
{
  _locked = false;
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
  return _locked;
}

