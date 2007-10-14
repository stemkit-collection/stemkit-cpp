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
  : _object(object), _name(object.getClass().getName())
{
  info() << "Created";
}

sk::rt::Logger::
Logger(const sk::util::String& name)
  : _object(*this), _name(name)
{
  info() << "Created";
}

sk::rt::Logger::
~Logger()
{
  info() << "Destroyed";
}

const sk::util::Class
sk::rt::Logger::
getClass() const
{
  return sk::util::Class("sk::rt::Logger");
}

const sk::util::String
sk::rt::Logger::
getScopeName() const
{
  return _name;
}

sk::rt::logger::Controller&
sk::rt::Logger::
controller() 
{
  return _controller;
}

const sk::rt::logger::Stream
sk::rt::Logger::
info(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("info", *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
fatal(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("fatal", *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
warning(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("warning", *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
notice(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("notice", *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
debug(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("debug", *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
detail(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream("detail", *this);
}
