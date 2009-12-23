/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/StringArray.h>

#include <sk/rt/StopWatch.h>

#include <sstream>
#include <iomanip>

static const sk::util::String __className("sk::rt::StopWatch");

sk::rt::StopWatch::
StopWatch()
  : _started(false), _stopped(false)
{
  init();
}

sk::rt::StopWatch::
~StopWatch()
{
}

const sk::util::Class
sk::rt::StopWatch::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::rt::StopWatch::
isTicking() const
{
  return _started == true && _stopped == false;
}

uint64_t
sk::rt::StopWatch::
getMilliseconds() const
{
  return getMicroseconds() / 1000;
}

const sk::util::String
sk::rt::StopWatch::
toString() const
{
  return toString(getMicroseconds());
}

const sk::util::String
sk::rt::StopWatch::
toString(uint64_t microseconds)
{
  uint64_t milliseconds = microseconds / 1000;
  uint64_t seconds = milliseconds / 1000;
  uint64_t minutes = seconds / 60;

  std::ostringstream stream;
  stream.fill('0');
  stream 
    << std::setw(2) << minutes / 60 << ':' 
    << std::setw(2) << minutes % 60 << ':' 
    << std::setw(2) << seconds % 60 << '.' 
    << std::setw(3) << milliseconds % 1000 << ','
    << std::setw(3) << microseconds % 1000
  ;
  return stream.str();
}

const sk::util::String
sk::rt::StopWatch::
inspect() const
{
  sk::util::StringArray depot;
  if(_started == false) {
    depot << "not started";
  }
  else if(_stopped == true) {
    depot << "stopped";
  }
  else {
    depot << "running";
  }
  depot << toString();

  return "<StopWatch: " + depot.join(", ") + '>';
}
