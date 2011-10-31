/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/rt/event/ExitingObserver.h>
#include <sk/rt/Event.h>

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <stdlib.h>

namespace {
  const sk::util::String __className("sk::rt::event::ExitingObserver");
}

sk::rt::event::ExitingObserver::
ExitingObserver(const int code)
  : _scope(__className), _code(code)
{
}

sk::rt::event::ExitingObserver::
~ExitingObserver()
{
}

const sk::util::Class
sk::rt::event::ExitingObserver::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::event::ExitingObserver::
processEvent(const sk::rt::Event& event)
{
  _scope.notice("Exiting") << "code=" << _code << ", event=" << event.inspect();
  ::exit(_code);

  return false;
}
