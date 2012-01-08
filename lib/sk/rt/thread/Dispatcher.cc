/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include "Dispatcher.h"
#include "Implementation.h"
#include "PrintingExceptionHandler.h"

sk::util::Holder<sk::rt::thread::Dispatcher> sk::rt::thread::Dispatcher::_mainHolder;
bool sk::rt::thread::Dispatcher::_mainAvailable = false;

static const char* __className("sk::rt::thread::Dispatcher");

sk::rt::thread::Dispatcher::
Dispatcher()
  : _sequence(0), _mutex(false), _uncaughtExceptionHandlerHolder(new PrintingExceptionHandler("thread-exception-handler"))
{
}

sk::rt::thread::Dispatcher::
~Dispatcher()
{
}

sk::rt::thread::Dispatcher&
sk::rt::thread::Dispatcher::
main()
{
  if(_mainHolder.isEmpty() == true) {
    _mainHolder.set(new Dispatcher);
    _mainAvailable = true;
  }
  return _mainHolder.getMutable();
}

void
sk::rt::thread::Dispatcher::
reset()
{
  _mainAvailable = false;
  _mainHolder.clear();
}

bool
sk::rt::thread::Dispatcher::
isMainAvailable()
{
  return _mainAvailable;
}

const sk::util::Class
sk::rt::thread::Dispatcher::
getClass() const
{
  return sk::util::Class(__className);
}

uint64_t
sk::rt::thread::Dispatcher::
makeSequence()
{
  _mutex.lock();
  uint64_t sequence = ++_sequence;
  _mutex.unlock();

  return sequence;
}

sk::rt::thread::Generic&
sk::rt::thread::Dispatcher::
currentThread()
{
  return Implementation::instance().getGeneric();
}

void
sk::rt::thread::Dispatcher::
setUncaughtExceptionHandler(thread::UncaughtExceptionHandler& handler)
{
  _uncaughtExceptionHandlerHolder.set(handler);
}

sk::rt::thread::UncaughtExceptionHandler&
sk::rt::thread::Dispatcher::
getUncaughtExceptionHandler() const
{
  return _uncaughtExceptionHandlerHolder.getMutable();
}

