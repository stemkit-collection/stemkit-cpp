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

#include <sk/rt/logger/Level.h>
#include <sk/rt/scope/Config.h>

#include <iostream>

sk::rt::scope::Config::
Config()
  : _streamHolder(std::cerr), _logPid(false), _logTime(false), _logObject(false),
    _levelHolder(logger::Level::ERROR)
{
}

sk::rt::scope::Config::
Config(const Config& other)
  : _streamHolder(other.getLogStream()), _logPid(other.isLogPid()), _logTime(other.isLogTime()), _logObject(other.isLogObject()),
    _levelHolder(other._levelHolder.get())
{
}

sk::rt::scope::Config::
~Config()
{
}

const sk::util::Class
sk::rt::scope::Config::
getClass() const
{
  return sk::util::Class("sk::rt::scope::Config");
}

void
sk::rt::scope::Config::
setLogStream(std::ostream& stream)
{
  _streamHolder.set(stream);
}

void 
sk::rt::scope::Config::
setLogLevel(const logger::Level& level)
{
  _levelHolder.set(level);
}

std::ostream&
sk::rt::scope::Config::
getLogStream() const
{
  return _streamHolder.get();
}

bool
sk::rt::scope::Config::
checkLogLevel(const sk::rt::logger::Level& level) const
{
  return level.toInt() <= _levelHolder.get().toInt();
}

void
sk::rt::scope::Config::
setLogPid(bool state) 
{
  _logPid = state;
}

void 
sk::rt::scope::Config::
setLogTime(bool state)
{
  _logTime = state;
}

void
sk::rt::scope::Config::
setLogObject(bool state)
{
  _logObject = state;
}

bool
sk::rt::scope::Config::
isLogPid() const 
{
  return _logPid;
}

bool
sk::rt::scope::Config::
isLogTime() const
{
  return _logTime;
}

bool
sk::rt::scope::Config::
isLogObject() const
{
  return _logObject;
}

const sk::util::String
sk::rt::scope::Config::
getProperty(const sk::util::String& name) const
{
  throw sk::util::MissingResourceException(name);
}

bool
sk::rt::scope::Config::
hasProperty(const sk::util::String& name) const
{
  return false;
}

void
sk::rt::scope::Config::
setProperty(const sk::util::String& name, const sk::util::String& value)
{
}
