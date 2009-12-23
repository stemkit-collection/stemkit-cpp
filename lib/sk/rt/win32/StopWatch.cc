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

#include <sk/rt/StopWatch.h>
#include <sk/rt/SystemException.h>

#include <windows.h>

struct sk::rt::StopWatch::Data : public virtual sk::util::Object {
  struct timeval start;
  struct timeval stop;
};

void
sk::rt::StopWatch::
init()
{
  _dataHolder.set(new Data);
}

namespace {
  int gettimeofday(struct timeval* tp, void* n) {
    LARGE_INTEGER ticksPerSecond;
    LARGE_INTEGER tick;   // A point in time
    LARGE_INTEGER time;   // For converting tick into real time

    // get the high resolution counter's accuracy
    // if this function failed, return 0
    if(QueryPerformanceFrequency(&ticksPerSecond) == 0) {
      return -1;
    }

    // what time is it?
    if(QueryPerformanceCounter(&tick) == 0) {
      return -1;
    }

    // convert the tick number into the number of seconds
    // since the system was started...
    time.QuadPart = tick.QuadPart / ticksPerSecond.QuadPart;

    tp->tv_sec = time.QuadPart; /* seconds */
    tp->tv_usec = (tick.QuadPart - (time.QuadPart * ticksPerSecond.QuadPart)) * 
                  1000000.0 / ticksPerSecond.QuadPart;

    return 0;
  }
  
  void obtain_current_time(struct timeval& timeinfo) {
    if(gettimeofday(&timeinfo, 0) != 0) {
      throw sk::rt::SystemException("gettimeofday");
    }
  }
}

void 
sk::rt::StopWatch::
start()
{
  obtain_current_time(_dataHolder.get().start);
  _started = true;
  _stopped = false;
}

void
sk::rt::StopWatch::
stop()
{
  if(isTicking() == true) {
    obtain_current_time(_dataHolder.get().stop);
    _stopped = true;
  }
}

uint64_t
sk::rt::StopWatch::
getMicroseconds() const
{
  if(_started == false) {
    return 0;
  }
  Data& data = _dataHolder.get();

  struct timeval last = data.stop;
  if(_stopped == false) {
    obtain_current_time(last);
  }
  return (last.tv_sec - data.start.tv_sec) * 1000000 + (last.tv_usec - data.start.tv_usec);
}
