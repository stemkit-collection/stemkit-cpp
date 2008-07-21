/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/rt/logger/Level.h>

std::vector<sk::rt::logger::Level*> sk::rt::logger::Level::_levels;

#define DEFINE_LEVEL(level) const sk::rt::logger::Level sk::rt::logger::Level::SK_L_##level(#level)

DEFINE_LEVEL(NONE);
DEFINE_LEVEL(ERROR);
DEFINE_LEVEL(STAT);
DEFINE_LEVEL(WARNING);
DEFINE_LEVEL(INFO);
DEFINE_LEVEL(NOTICE);
DEFINE_LEVEL(DETAIL);
DEFINE_LEVEL(DEBUG);

sk::rt::logger::Level::
Level(const sk::util::String& name)
  : _name(name), _value(_levels.size())
{
  _levels.push_back(this);
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

int 
sk::rt::logger::Level::
toInt() const
{
  return _value;
}

bool
sk::rt::logger::Level::
operator==(const Level& other) const
{
  return _value == other._value;
}

const sk::util::String
sk::rt::logger::Level::
toString() const
{
  return getName();
}

const sk::rt::logger::Level&
sk::rt::logger::Level::
valueOf(const sk::util::String& name)
{
  for(std::vector<Level*>::iterator iterator = _levels.begin(); iterator != _levels.end() ;++iterator) {
    if(name.equalsIgnoreCase((*iterator)->getName())) {
      return *(*iterator);
    }
  }
  return SK_L_NONE;
}
