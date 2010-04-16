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
  : _stream(0), _label(label), _config(scope.getConfig()), _enabled(_config.checkLogLevel(level)), _level(level), _scope(scope), 
    _memory(false)
{
}

sk::rt::logger::Stream::
~Stream()
{
  if(_stream != 0) {
    std::ostringstream& stream = *_stream;
    if(_memory == true && _config.isLogMemory() == true) {
      try {
        uint64_t memory = sk::rt::ProcessInfo::current().virtualMemory(_scope.getLock());
        stream << " [" << (memory >> 10) << "K]";
      }
      catch(const std::exception& exception) {
        stream << " [??? - " << exception.what() << "]";
      }
    }
    stream << _config.getLineTerminator();
    _config.getLogDestination().dispatch(stream.str().c_str(), stream.str().size());

    delete _stream;
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
    stream << ':' << std::hex << _scope.getObject().getId() << std::dec;
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
  if(_stream == 0) {
    _stream = new std::ostringstream;
    makeHeader(*_stream);
  }
  return *_stream;
}
