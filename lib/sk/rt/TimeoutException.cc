/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/rt/TimeoutException.h>

static const sk::util::String __className("sk::rt::TimeoutException");

sk::rt::TimeoutException::
TimeoutException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("Timeout") << message)
{
}

sk::rt::TimeoutException::
TimeoutException()
  : sk::util::Exception("Timeout")
{
}

const sk::util::Class
sk::rt::TimeoutException::
getClass() const
{
  return sk::util::Class(__className);
}
