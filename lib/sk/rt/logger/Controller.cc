/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/rt/logger/Controller.h>
#include <sk/rt/logger/Level.h>
#include <iostream>

sk::rt::logger::Controller::
Controller()
  : _streamHolder(std::cerr), _showPid(false), _showTime(false), _showObject(false)
{
}

sk::rt::logger::Controller::
~Controller()
{
}

const sk::util::Class
sk::rt::logger::Controller::
getClass() const
{
  return sk::util::Class("sk::rt::logger::Controller");
}

sk::rt::logger::Config& 
sk::rt::logger::Controller::
findConfig(const sk::util::String& name)
{
  return *this;
}

void
sk::rt::logger::Controller::
setStream(std::ostream& stream)
{
  _streamHolder.set(stream);
}

void 
sk::rt::logger::Controller::
setLevel(const Level& level)
{
  _levelHolder.set(level);
}

std::ostream&
sk::rt::logger::Controller::
getStream() const
{
  return _streamHolder.get();
}

const sk::rt::logger::Level&
sk::rt::logger::Controller::
getLevel() const
{
  return _levelHolder.isEmpty() == false ? _levelHolder.get() : Level::ERROR;
}

bool
sk::rt::logger::Controller::
checkLevel(const sk::rt::logger::Level& level) const
{
  return level.toInt() <= getLevel().toInt();
}

void
sk::rt::logger::Controller::
setShowPid(bool state) 
{
  _showPid = state;
}

void 
sk::rt::logger::Controller::
setShowTime(bool state)
{
  _showTime = state;
}

void
sk::rt::logger::Controller::
setShowObject(bool state)
{
  _showObject = state;
}

bool
sk::rt::logger::Controller::
isShowPid() const 
{
  return _showPid;
}

bool
sk::rt::logger::Controller::
isShowTime() const
{
  return _showTime;
}

bool
sk::rt::logger::Controller::
isShowObject() const
{
  return _showObject;
}
