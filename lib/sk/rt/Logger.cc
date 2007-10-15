/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/Logger.h>
#include <sk/rt/logger/Level.h>

sk::rt::logger::Controller sk::rt::Logger::_controller;

sk::rt::Logger::
Logger(const sk::util::Object& object)
  : _parent(*this), _object(object), _name(object.getClass().getName()), _config(_controller.findConfig(_name))
{
  info() << "Enter (object)";
}

sk::rt::Logger::
Logger(const Logger& other)
  : _parent(&other._parent == &other ? *this : other._parent),
    _object(&other._object == &other ? *this : other._object),
    _name(other._name), _config(other._config)
{
  info() << "Enter (copy)";
}

sk::rt::Logger::
Logger(const sk::util::String& name)
  : _parent(*this), _object(*this), _name(name), _config(_controller.findConfig(_name))
{
  info() << "Enter (name)";
}

sk::rt::Logger::
Logger(const Logger& parent, const sk::util::String& name)
  : _parent(parent), _object(parent.getObject()), _name(name), _config(parent.getConfig())
{
  info() << "Enter (scope)";
}

sk::rt::Logger::
~Logger()
{
  info() << "Leave";
}

const sk::util::Class
sk::rt::Logger::
getClass() const
{
  return sk::util::Class("sk::rt::Logger");
}

void
sk::rt::Logger::
serializeScope(std::ostream& stream) const
{
  if(&_parent != this) {
    _parent.serializeScope(stream);
    stream << '#';
  }
  stream << _name;
}

const sk::util::Object&
sk::rt::Logger::
getObject() const
{
  return _object;
}

sk::rt::logger::Controller&
sk::rt::Logger::
controller() 
{
  return _controller;
}

const sk::rt::logger::Config&
sk::rt::Logger::
getConfig() const
{
  return _config;
}

const sk::rt::logger::Stream
sk::rt::Logger::
info(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::INFO, *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
error(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::ERROR, *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
warning(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::WARNING, *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
notice(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::NOTICE, *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
debug(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::DEBUG, *this);
}

const sk::rt::logger::Stream
sk::rt::Logger::
detail(const sk::rt::logger::Spot& spot) const
{
  return sk::rt::logger::Stream(logger::Level::DETAIL, *this);
}

const sk::rt::Logger
sk::rt::Logger::
scope(const sk::util::String& name) const
{
  return Logger(*this, name);
}
