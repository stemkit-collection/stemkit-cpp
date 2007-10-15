/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Stream.h>
#include <sk/rt/logger/Config.h>

#include <iostream>

sk::rt::logger::Stream::
Stream(const Level& level, const ScopeProvider& provider)
  : _enabled(provider.config().checkLevel(level)), _stream(provider.config().getStream()) 
{
  if(isEnabled() == true) {
    const Config& config = provider.config();

    if(config.isShowPid() == true) {
      _stream << '[' << getpid() << "] ";
    }
    if(config.isShowTime() == true) {
      char buffer[32];
      time_t now = time(0);
      strftime(buffer, sizeof(buffer), "%y/%m/%d %H:%M:%S", localtime(&now));
      _stream << buffer << ' ';
    }

    _stream << level.getName() << ":" << provider.getScopeName();
    if(config.isShowObject() == true) {
      _stream << ':' << &provider.getObject();
    }
    _stream << ": ";
  }
}

sk::rt::logger::Stream::
~Stream()
{
  if(isEnabled() == true) {
    getStream() << std::endl;
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
