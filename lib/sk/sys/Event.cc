/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/sys/Event.h>
#include <sk/sys/event/Dispatcher.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

namespace {
  const sk::util::String __className("sk::sys::Event");
  sk::util::Holder<sk::sys::event::Dispatcher> __dispatcherHolder;
}

sk::sys::Event::
Event()
{
}

sk::sys::Event::
~Event()
{
}

const sk::util::Class
sk::sys::Event::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::sys::Event::
setup()
{
  if(__dispatcherHolder.isEmpty() == true) {
    __dispatcherHolder.set(new sk::sys::event::Dispatcher);
  }
}

void 
sk::sys::Event::
reset()
{
  __dispatcherHolder.clear();
}

sk::sys::event::Dispatcher& 
sk::sys::Event::
dispatcher()
{
  setup();

  return __dispatcherHolder.getMutable();
}
