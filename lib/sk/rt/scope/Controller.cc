/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/MissingResourceException.h>

#include <sk/rt/scope/Controller.h>
#include <sk/rt/logger/Level.h>
#include <iostream>

sk::rt::scope::Controller::
Controller()
  : _streamHolder(std::cerr), _showPid(false), _showTime(false), _showObject(false),
    _levelHolder(logger::Level::ERROR)
{
}

sk::rt::scope::Controller::
~Controller()
{
}

const sk::util::Class
sk::rt::scope::Controller::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Controller");
}

sk::rt::scope::Config& 
sk::rt::scope::Controller::
findConfig(const sk::util::String& name)
{
  return *this;
}

void
sk::rt::scope::Controller::
setStream(std::ostream& stream)
{
  _streamHolder.set(stream);
}

void 
sk::rt::scope::Controller::
setLevel(const logger::Level& level)
{
  _levelHolder.set(level);
}

std::ostream&
sk::rt::scope::Controller::
getStream() const
{
  return _streamHolder.get();
}

bool
sk::rt::scope::Controller::
checkLevel(const sk::rt::logger::Level& level) const
{
  return level.toInt() <= _levelHolder.get().toInt();
}

void
sk::rt::scope::Controller::
setShowPid(bool state) 
{
  _showPid = state;
}

void 
sk::rt::scope::Controller::
setShowTime(bool state)
{
  _showTime = state;
}

void
sk::rt::scope::Controller::
setShowObject(bool state)
{
  _showObject = state;
}

bool
sk::rt::scope::Controller::
isShowPid() const 
{
  return _showPid;
}

bool
sk::rt::scope::Controller::
isShowTime() const
{
  return _showTime;
}

bool
sk::rt::scope::Controller::
isShowObject() const
{
  return _showObject;
}

const sk::util::String
sk::rt::scope::Controller::
getProperty(const sk::util::String& name) const
{
  throw sk::util::MissingResourceException(name);
}

bool
sk::rt::scope::Controller::
hasProperty(const sk::util::String& name) const
{
  return false;
}
