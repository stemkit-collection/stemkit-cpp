/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/rt/Event.h>
#include <sk/rt/event/Dispatcher.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

namespace {
  const sk::util::String __className("sk::rt::Event");
  sk::util::Holder<sk::rt::event::Dispatcher> __dispatcherHolder;
}

sk::rt::Event::
Event()
{
}

sk::rt::Event::
~Event()
{
}

const sk::util::Class
sk::rt::Event::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::rt::Event::
setup()
{
  if(__dispatcherHolder.isEmpty() == true) {
    __dispatcherHolder.set(new sk::rt::event::Dispatcher);
  }
}

void 
sk::rt::Event::
reset()
{
  __dispatcherHolder.clear();
}

sk::rt::event::Dispatcher& 
sk::rt::Event::
dispatcher()
{
  setup();

  return __dispatcherHolder.getMutable();
}
