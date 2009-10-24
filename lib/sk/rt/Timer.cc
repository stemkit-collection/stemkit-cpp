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

#include <sk/rt/Timer.h>
#include <sk/rt/SystemException.h>

static const sk::util::String __className("sk::rt::Timer");

sk::rt::Timer::
Timer()
  : _started(false), _stopped(false)
{
}

sk::rt::Timer::
~Timer()
{
}

const sk::util::Class
sk::rt::Timer::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  void obtain_current_time(struct timeval& timeinfo) {
    if(gettimeofday(&timeinfo, 0) != 0) {
      throw sk::rt::SystemException("gettimeofday");
    }
  }
}

void 
sk::rt::Timer::
start()
{
  obtain_current_time(_start);
  _started = true;
  _stopped = false;
}

void
sk::rt::Timer::
stop()
{
  obtain_current_time(_stop);
  _stopped = _started;
}

bool
sk::rt::Timer::
isTicking() const
{
  return _started == true && _stopped == false;
}
