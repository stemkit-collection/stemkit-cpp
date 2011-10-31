/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/sys/event/IgnoringObserver.h>
#include <sk/sys/Event.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>

namespace {
  const sk::util::String __className("sk::sys::event::IgnoringObserver");
}

sk::sys::event::IgnoringObserver::
IgnoringObserver()
  : _scope(__className)
{
}

sk::sys::event::IgnoringObserver::
~IgnoringObserver()
{
}

const sk::util::Class
sk::sys::event::IgnoringObserver::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::sys::event::IgnoringObserver::
processEvent(const sk::sys::Event& event)
{
  _scope.notice("Ignoring") << event.inspect();
  return true;
}
