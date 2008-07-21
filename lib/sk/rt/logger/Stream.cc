/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Stream.h>
#include <sk/rt/logger/IConfig.h>

#include <unistd.h>
#include <time.h>

sk::rt::logger::Stream::
Stream(const sk::util::String& label, const Level& level, const logger::IScope& scope)
  : _config(scope.getConfig()), _enabled(_config.checkLogLevel(level))
{
  if(isEnabled() == true) {
    if(_config.isLogPid() == true) {
      _stream << getpid() << ' ';
    }
    if(_config.isLogTime() == true) {
      char buffer[64];
      time_t now = time(0);
      strftime(buffer, sizeof(buffer), _config.getTimeFormat(), localtime(&now));
      _stream << buffer << ' ';
    }

    _stream << level.getName() << ':';
    scope.agregateScopeName(_stream);

    if(_config.isLogObject() == true) {
      _stream << ':' << &scope.getObject();
    }
    if(&label != &sk::util::String::EMPTY) {
      _stream << ':' << label;
    }
    _stream << ": ";
  }
}

sk::rt::logger::Stream::
~Stream()
{
  if(isEnabled() == true) {
    _stream << std::endl;
    _config.getLogDestination().dispatch(_stream.str().c_str(), _stream.str().size());
  }
}

const sk::util::Class
sk::rt::logger::Stream::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Stream");
}

bool
sk::rt::logger::Stream::
isEnabled() const
{
  return _enabled;
}

std::ostream&
sk::rt::logger::Stream::
getStream() const
{
  return _stream;
}
