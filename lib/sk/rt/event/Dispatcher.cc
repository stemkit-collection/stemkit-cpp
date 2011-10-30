/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/event/Dispatcher.h>

static const sk::util::String __className("sk::rt::event::Dispatcher");

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
