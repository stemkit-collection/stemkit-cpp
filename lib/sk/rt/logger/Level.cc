/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Level.h>

int sk::rt::logger::Level::_counter = 0;

#define DEFINE_LEVEL(level) const sk::rt::logger::Level sk::rt::logger::Level::level(#level)

DEFINE_LEVEL(ERROR);
DEFINE_LEVEL(WARNING);
DEFINE_LEVEL(NOTICE);
DEFINE_LEVEL(INFO);
DEFINE_LEVEL(DETAIL);
DEFINE_LEVEL(DEBUG);

sk::rt::logger::Level::
Level(const sk::util::String& name)
  : _name(name), _value(++_counter)
{
}

sk::rt::logger::Level::
~Level()
{
}

const sk::util::Class
sk::rt::logger::Level::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Level");
}

const sk::util::String&
sk::rt::logger::Level::
getName() const 
{
  return _name;
}

bool
sk::rt::logger::Level::
operator==(const Level& other) const
{
  return _value == other._value;
}
