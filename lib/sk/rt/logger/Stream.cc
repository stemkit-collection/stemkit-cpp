/*  vim: set sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
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
  : _requested(false), _label(label), _config(scope.getConfig()), _enabled(_config.checkLogLevel(level)), _level(level), _scope(scope)
{
}

sk::rt::logger::Stream::
~Stream()
{
  if(_requested == true) {
    _stream << _config.getLineTerminator();
    _config.getLogDestination().dispatch(_stream.str().c_str(), _stream.str().size());
  }
}

void
sk::rt::logger::Stream::
makeHeader(std::ostream& stream) const
{
  if(_config.isLogPid() == true) {
    stream << getpid() << ' ';
  }
  if(_config.isLogTime() == true) {
    char buffer[64];
    time_t now = time(0);
    struct tm tm_buffer;

    strftime(buffer, sizeof(buffer), _config.getTimeFormat(), localtime_r(&now, &tm_buffer));
    stream << buffer << ' ';
  }

  stream << _level.getName() << ':';
  _scope.aggregateScopeName(stream);

  if(_config.isLogObject() == true) {
    stream << ':' << &_scope.getObject();
  }
  if(_config.isLogThread() == true) {
    stream << ':' << _scope.currentThreadId();
  }
  if(&_label != &sk::util::String::EMPTY) {
    stream << ':' << _label;
  }
  stream << ": ";
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
  if(_requested == false) {
    _requested = true;
    makeHeader(_stream);
  }
  return _stream;
}
