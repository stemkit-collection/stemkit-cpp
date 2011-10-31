/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/sys/event/Dispatcher.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

namespace {
  const sk::util::String __className("sk::sys::event::Dispatcher");
}

sk::sys::event::Dispatcher::
Dispatcher()
{
}

sk::sys::event::Dispatcher::
~Dispatcher()
{
}

const sk::util::Class
sk::sys::event::Dispatcher::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::sys::event::Dispatcher::
addEventObserver(const sk::sys::Event& event, const sk::sys::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::event::Dispatcher::
removeEventObserver(const sk::sys::Event& event, const sk::sys::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::event::Dispatcher::
removeEventObservers(const sk::sys::Event& event)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::event::Dispatcher::
removeEventsObserver(const sk::sys::event::Observer& observer)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::event::Dispatcher::
clear()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::sys::event::Dispatcher::
listenAndDispatch()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
