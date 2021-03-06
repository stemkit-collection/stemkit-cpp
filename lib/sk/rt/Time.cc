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
#include <sk/util/Strings.h>

#include <sk/rt/Time.h>
#include <time.h>

static const char* __className("sk::rt::Time");

sk::rt::Time::
Time(time_t seconds, uint32_t microseconds)
  : _seconds(seconds), _microseconds(microseconds)
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
  struct timeval moment;
  obtainCurrentTime(moment);
  return Time(moment.tv_sec, moment.tv_usec);
}

const sk::rt::Time
sk::rt::Time::
at(time_t seconds, uint32_t microseconds)
{
  return Time(seconds, microseconds);
}

const sk::rt::Time
sk::rt::Time::
at(time_t seconds)
{
  return at(seconds, 0);
}

const sk::util::String
sk::rt::Time::
format(const sk::util::String& specification) const
{
  char buffer[1024];
  struct tm tm_buffer;
  strftime(buffer, sizeof(buffer), specification.getChars(), &makeLocaltime(tm_buffer));
  return buffer;
}

const sk::util::String
sk::rt::Time::
inspect() const
{
  sk::util::Strings depot;

  depot << "date=" + format("%y/%m/%d");
  depot << "time=" + format("%H:%M:%S") + '.' + sk::util::String::valueOf(_microseconds);

  return "<Time: " + depot.join(", ") + '>';
}

const sk::util::String
sk::rt::Time::
toString() const
{
  return format("%c");
}

time_t
sk::rt::Time::
getSeconds() const
{
  return _seconds;
}

uint32_t
sk::rt::Time::
getMicroseconds() const
{
  return _microseconds;
}

const sk::rt::Time
sk::rt::Time::
offsetMilliseconds(uint64_t milliseconds) const
{
  return Time(_seconds + (milliseconds / 1000), _microseconds + ((milliseconds % 1000) * 1000));
}

bool
sk::rt::
operator==(const sk::rt::Time& first, const sk::rt::Time& second)
{
  return (first.getSeconds() == second.getSeconds()) && (first.getMicroseconds() == second.getMicroseconds());
}

bool
sk::rt::
operator!=(const sk::rt::Time& first, const sk::rt::Time& second)
{
  return !(first == second);
}

bool
sk::rt::
operator<(const sk::rt::Time& first, const sk::rt::Time& second)
{
  time_t s1 = first.getSeconds();
  time_t s2 = second.getSeconds();

  if(s1 < s2) {
    return true;
  }
  if(s1 == s2) {
    return first.getMicroseconds() < second.getMicroseconds();
  }
  return false;
}

bool
sk::rt::
operator<=(const sk::rt::Time& first, const sk::rt::Time& second)
{
  return (first == second) || (first < second);
}

bool
sk::rt::
operator>(const sk::rt::Time& first, const sk::rt::Time& second)
{
  return !(first <= second);
}

bool
sk::rt::
operator>=(const sk::rt::Time& first, const sk::rt::Time& second)
{
  return !(first < second);
}
