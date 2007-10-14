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
#include "DisablingConfig.h"

sk::rt::logger::Controller::
Controller()
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
  static DisablingConfig config(*this);
  return config;
}

void
sk::rt::logger::Controller::
setStream(std::ostream& stream)
{
  _streamHolder.set(stream);
}

std::ostream&
sk::rt::logger::Controller::
getStream() const
{
  return _streamHolder.get();
}
