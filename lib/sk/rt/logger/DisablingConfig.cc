/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/IllegalStateException.h>

#include <sk/rt/logger/IController.h>
#include <sk/rt/logger/Level.h>
#include "DisablingConfig.h"

sk::rt::logger::DisablingConfig::
DisablingConfig(IController& controller)
  : _controller(controller)
{
}

sk::rt::logger::DisablingConfig::
~DisablingConfig()
{
}

const sk::util::Class
sk::rt::logger::DisablingConfig::
getClass() const
{
  return sk::util::Class("sk::rt::logger::DisablingConfig");
}

bool
sk::rt::logger::DisablingConfig::
checkLevel(const sk::rt::logger::Level& level) const
{
  return level == Level::ERROR;
}

std::ostream&
sk::rt::logger::DisablingConfig::
stream() const
{
  return _controller.getStream();
}
