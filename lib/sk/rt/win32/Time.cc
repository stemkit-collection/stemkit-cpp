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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/rt/SystemException.h>

#include <sk/rt/Time.h>
#include <time.h>

const struct tm&
sk::rt::Time::
makeLocaltime(struct tm& tm_buffer) const
{
  localtime_s(&tm_buffer, &_seconds);
  return tm_buffer;
}

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#  define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#  define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
namespace {
  int gettimeofday_as_filetime(struct timeval* tv, void* tz) {
    FILETIME ft;

    unsigned __int64 tmpres = 0;
    static int tzflag;
     
    if(tv != 0) {
      GetSystemTimeAsFileTime(&ft);
       
      tmpres |= ft.dwHighDateTime;
      tmpres <<= 32;
      tmpres |= ft.dwLowDateTime;
       
      /*converting file time to unix epoch*/
      tmpres /= 10;  /*convert into microseconds*/
      tmpres -= DELTA_EPOCH_IN_MICROSECS;
      tv->tv_sec = (long)(tmpres / 1000000UL);
      tv->tv_usec = (long)(tmpres % 1000000UL);
    }
    return 0;
  }
  
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
}

void 
sk::rt::Time::
obtainCurrentTime(struct timeval& timeinfo) 
{
  if(gettimeofday(&timeinfo, 0) != 0) {
    throw sk::rt::SystemException("gettimeofday");
  }
}
