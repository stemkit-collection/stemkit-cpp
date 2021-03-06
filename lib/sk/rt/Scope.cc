/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/Boolean.h>

#include <sk/rt/Scope.h>
#include <sk/rt/scope/Arbitrator.h>
#include <sk/rt/logger/Level.h>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NumberFormatException.h>

sk::rt::scope::Controller* sk::rt::Scope::_controller = 0;

sk::rt::Scope::
Scope(const sk::util::Object& object)
  : _parent(*this), _object(object), _name(object.getClass().getName()), _aggregator(controller().getAggregator().obtain(_name))
{
  detail().memory() << "Enter (object)";
}

sk::rt::Scope::
Scope(const Scope& other)
  : _parent(&other._parent == &other ? *this : other._parent),
    _object(&other._object == &other ? *this : other._object),
    _name(other._name), _aggregator(other._aggregator)
{
  detail().memory() << "Enter (copy)";
}

sk::rt::Scope::
Scope(const sk::util::String& name)
  : _parent(*this), _object(*this), _name(name), _aggregator(controller().getAggregator().obtain(name))
{
  detail().memory() << "Enter (name)";
}

sk::rt::Scope::
Scope(const Scope& parent, const sk::util::String& name)
  : _parent(parent), _object(*this), _name(name), _aggregator(parent.getAggregator().obtain(name))
{
  detail().memory() << "Enter (scope)";
}

sk::rt::Scope::
~Scope()
{
  detail().memory() << "Leave";
}

sk::rt::Scope&
sk::rt::Scope::
operator = (const Scope& other)
{
  return *this;
}

const sk::util::Class
sk::rt::Scope::
getClass() const
{
  return sk::util::Class("sk::rt::Scope");
}

const sk::util::String
sk::rt::Scope::
getName() const
{
  return _name;
}

void
sk::rt::Scope::
aggregateScopeName(std::ostream& stream) const
{
  if(&_parent != this) {
    _parent.aggregateScopeName(stream);
    stream << '#';
  }
  stream << _name;
}

const sk::util::Object&
sk::rt::Scope::
getObject() const
{
  return _object;
}

sk::rt::scope::Controller&
sk::rt::Scope::
controller()
{
  if(_controller == 0) {
    _controller = new scope::Controller;
  }
  return *_controller;
}

sk::rt::scope::Aggregator&
sk::rt::Scope::
getAggregator() const
{
  return _aggregator;
}

uint64_t
sk::rt::Scope::
currentThreadId() const
{
  return _aggregator.getArbitrator().currentThreadId();
}

sk::rt::Lock&
sk::rt::Scope::
getLock() const
{
  return _aggregator.getArbitrator();
}

const sk::rt::scope::IConfig&
sk::rt::Scope::
getConfig() const
{
  return _aggregator.getConfig();
}

const sk::rt::logger::Stream
sk::rt::Scope::
error(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_ERROR, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
warning(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_WARNING, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
stat(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_STAT, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
info(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_INFO, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
notice(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_NOTICE, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
debug(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_DEBUG, *this);
}

const sk::rt::logger::Stream
sk::rt::Scope::
detail(const sk::util::String& label) const
{
  return sk::rt::logger::Stream(label, logger::Level::SK_L_DETAIL, *this);
}

const sk::rt::Scope
sk::rt::Scope::
scope(const sk::util::String& name) const
{
  return Scope(*this, name);
}

const sk::util::String
sk::rt::Scope::
getProperty(const sk::util::String& name) const
{
  return getConfig().getProperty(name);
}

bool
sk::rt::Scope::
hasProperty(const sk::util::String& name) const
{
  return getConfig().hasProperty(name);
}

const sk::util::String
sk::rt::Scope::
getProperty(const sk::util::String& name, const sk::util::String& fallback) const
{
  return getConfig().getProperty(name, fallback);
}

const sk::util::String
sk::rt::Scope::
getProperty(const sk::util::String& name, const char* fallback) const
{
  return getConfig().getProperty(name, fallback);
}

int
sk::rt::Scope::
getProperty(const sk::util::String& name, int fallback) const
{
  return getConfig().getProperty(name, fallback);
}

bool
sk::rt::Scope::
getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const
{
  return getConfig().getProperty(name, fallback);
}
