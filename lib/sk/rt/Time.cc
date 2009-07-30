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

#include <sk/rt/Time.h>
#include <time.h>

static const char* __className("sk::rt::Time");

sk::rt::Time::
Time()
  : _time(time(0))
{
}

sk::rt::Time::
~Time()
{
}

const sk::util::Class
sk::rt::Time::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::rt::Time
sk::rt::Time::
now() 
{
  return Time();
}

const sk::util::String
sk::rt::Time::
format(const sk::util::String& specification) const
{
  char buffer[1024];
  struct tm tm_buffer;
  strftime(buffer, sizeof(buffer), specification.getChars(), &figure_localtime(tm_buffer));
  return buffer;
}
