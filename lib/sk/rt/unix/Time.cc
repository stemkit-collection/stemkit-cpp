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
#include <sys/time.h>

const struct tm&
sk::rt::Time::
makeLocaltime(struct tm& tm_buffer) const
{
  ::localtime_r(&_seconds, &tm_buffer);
  return tm_buffer;
}

void 
sk::rt::Time::
obtainCurrentTime(struct timeval& timeinfo) 
{
  if(::gettimeofday(&timeinfo, 0) != 0) {
    throw sk::rt::SystemException("gettimeofday");
  }
}
