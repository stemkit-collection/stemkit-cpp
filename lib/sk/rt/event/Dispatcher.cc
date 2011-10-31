/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/rt/event/Dispatcher.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

namespace {
  const sk::util::String __className("sk::rt::event::Dispatcher");
}

sk::rt::event::Dispatcher::
Dispatcher()
{
}

sk::rt::event::Dispatcher::
~Dispatcher()
{
}

const sk::util::Class
sk::rt::event::Dispatcher::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::event::Dispatcher::
addEventObserver(const sk::rt::Event& event, const sk::rt::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::event::Dispatcher::
removeEventObserver(const sk::rt::Event& event, const sk::rt::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::event::Dispatcher::
removeEventObservers(const sk::rt::Event& event)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::event::Dispatcher::
removeEventsObserver(const sk::rt::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::event::Dispatcher::
clear()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::rt::event::Dispatcher::
listenAndDispatch()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
