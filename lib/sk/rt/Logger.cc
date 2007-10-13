/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/Logger.h>

sk::rt::logger::Controller sk::rt::Logger::_controller;

sk::rt::Logger::
Logger(const sk::util::Object& object)
{
}

sk::rt::Logger::
Logger(const sk::util::String& name)
{
}

sk::rt::Logger::
~Logger()
{
}

const sk::util::Class
sk::rt::Logger::
getClass() const
{
  return sk::util::Class("sk::rt::Logger");
}

sk::rt::logger::Controller&
sk::rt::Logger::
controller() 
{
  return _controller;
}
