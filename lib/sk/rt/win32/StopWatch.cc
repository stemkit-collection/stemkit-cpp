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
};

void
sk::rt::StopWatch::
init()
{
  _dataHolder.set(new Data);
}

namespace {
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
