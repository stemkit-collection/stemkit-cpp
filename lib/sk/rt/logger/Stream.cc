/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Stream.h>

sk::rt::logger::Stream::
Stream(bool enabled, const Level& level, const ScopeProvider& provider)
  : _enabled(enabled), _level(level), _provider(provider) 
{
}

sk::rt::logger::Stream::
~Stream()
{
}

const sk::util::Class
sk::rt::logger::Stream::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Stream");
}

const sk::util::String
sk::rt::logger::Stream::
getScopeName() const
{
  return _provider.getScopeName();
}

const sk::rt::logger::Level&
sk::rt::logger::Stream::
getLevel() const 
{
  return _level;
}

bool
sk::rt::logger::Stream::
isEnabled() const
{
  return _enabled;
}
