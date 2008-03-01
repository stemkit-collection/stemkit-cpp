/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>
#include <sk/util/Integer.h>
#include <sk/util/Holder.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NumberFormatException.h>

#include <sk/rt/logger/Level.h>
#include <scope/Config.h>
#include <logger/ExternalStreamDestination.h>

#include <iostream>

sk::rt::scope::Config::
Config()
  : _destinationHolder(new logger::ExternalStreamDestination(std::cerr)), 
    _levelHolder(logger::Level::INFO), _timeFormat("%y/%m/%d %H:%M:%S"),
    _logPid(false), _logTime(false), _logObject(false)
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
setLogDestination(const logger::Destination& destination)
{
  _destinationHolder.set(destination.clone());
}

void 
sk::rt::scope::Config::
setLogLevel(const logger::Level& level)
{
  _levelHolder.set(level);
}

void 
sk::rt::scope::Config::
setTimeFormat(const sk::util::String& format)
{
  _timeFormat = format;
}

sk::rt::logger::Destination& 
sk::rt::scope::Config::
getLogDestination() const
{
  return _destinationHolder.get();
}

bool
sk::rt::scope::Config::
checkLogLevel(const sk::rt::logger::Level& level) const
{
  return level.toInt() <= _levelHolder.get().toInt();
}

const char*
sk::rt::scope::Config::
getTimeFormat() const
{
  return _timeFormat.getChars();
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
  registry::const_iterator iterator = _properties.find(name);
  if(iterator != _properties.end()) {
    return iterator->second;
  }
  throw sk::util::MissingResourceException(name);
}

const sk::util::String 
sk::rt::scope::Config::
getProperty(const sk::util::String& name, const sk::util::String& fallback) const
{
  registry::const_iterator iterator = _properties.find(name);
  if(iterator != _properties.end()) {
    return iterator->second;
  }
  return fallback;
}

const sk::util::String 
sk::rt::scope::Config::
getProperty(const sk::util::String& name, const char* fallback) const
{
  return getProperty(name, sk::util::String(fallback));
}

bool 
sk::rt::scope::Config::
getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const
{
  registry::const_iterator iterator = _properties.find(name);
  if(iterator != _properties.end()) {
    return sk::util::Boolean::parseBoolean(iterator->second);
  }
  return fallback.booleanValue();
}

int 
sk::rt::scope::Config::
getProperty(const sk::util::String& name, int fallback) const
{
  registry::const_iterator iterator = _properties.find(name);
  if(iterator != _properties.end()) {
    try {
      return sk::util::Integer::parseInt(iterator->second);
    }
    catch(const sk::util::NumberFormatException& exception) {}
  }
  return fallback;
}

bool
sk::rt::scope::Config::
hasProperty(const sk::util::String& name) const
{
  return _properties.find(name) != _properties.end();
}

void
sk::rt::scope::Config::
setProperty(const sk::util::String& name, const sk::util::String& value)
{
  _properties[name] = value;
}
