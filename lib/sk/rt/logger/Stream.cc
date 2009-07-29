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
#include <sk/rt/logger/IScope.h>
#include <sk/rt/logger/IConfig.h>
#include <sk/rt/Time.h>
#include <sk/rt/ProcessInfo.h>

sk::rt::logger::Stream::
Stream(const sk::util::String& label, const Level& level, const logger::IScope& scope)
  : _requested(false), _label(label), _config(scope.getConfig()), _enabled(_config.checkLogLevel(level)), _level(level), _scope(scope), 
    _memory(false)
{
}

sk::rt::logger::Stream::
~Stream()
{
  if(_requested == true) {
    if(_memory == true && _config.isLogMemory() == true) {
      uint64_t memory = sk::rt::ProcessInfo::current().virtualMemory(_scope.getLock());
      _stream << " [" << (memory >> 10) << "K]";
    }
    _stream << _config.getLineTerminator();
    _config.getLogDestination().dispatch(_stream.str().c_str(), _stream.str().size());
  }
}

const sk::rt::logger::Stream&
sk::rt::logger::Stream::
memory() const
{
  _memory = true;
  return *this;
}

void
sk::rt::logger::Stream::
makeHeader(std::ostream& stream) const
{
  if(_config.isLogPid() == true) {
    stream << sk::rt::ProcessInfo::current().pid() << ' ';
  }
  if(_config.isLogTime() == true) {
    stream << sk::rt::Time::now().format(_config.getTimeFormat()) << ' ';
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
