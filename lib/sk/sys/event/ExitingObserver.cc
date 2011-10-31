/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/sys/event/ExitingObserver.h>
#include <sk/sys/Event.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <stdlib.h>

namespace {
  const sk::util::String __className("sk::sys::event::ExitingObserver");
}

sk::sys::event::ExitingObserver::
ExitingObserver(const int code)
  : _scope(__className), _code(code)
{
}

sk::sys::event::ExitingObserver::
~ExitingObserver()
{
}

const sk::util::Class
sk::sys::event::ExitingObserver::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::sys::event::ExitingObserver::
processEvent(const sk::sys::Event& event)
{
  _scope.notice("Exiting") << "code=" << _code << ", event=" << event.inspect();
  ::exit(_code);

  return false;
}
