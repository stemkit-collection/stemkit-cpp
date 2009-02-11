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

sk::util::Holder<sk::rt::thread::Dispatcher> sk::rt::thread::Dispatcher::_mainHolder;
static const sk::util::Class __class("sk::rt::thread::Dispatcher");

sk::rt::thread::Dispatcher::
Dispatcher()
  : _sequence(0), _mutex(false)
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
  }
  return _mainHolder.get();
}

void
sk::rt::thread::Dispatcher::
reset()
{
  _mainHolder.clear();
}

const sk::util::Class
sk::rt::thread::Dispatcher::
getClass() const
{
  return __class;
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
