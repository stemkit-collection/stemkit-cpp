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
#include <sk/util/Strings.h>

#include <sk/util/IllegalArgumentException.h>

static const sk::util::String __className("sk::util::IllegalArgumentException");

sk::util::IllegalArgumentException::
IllegalArgumentException(const sk::util::String& message)
  : sk::util::Exception(sk::util::Strings("Illegal argument") << message)
{
}

sk::util::IllegalArgumentException::
IllegalArgumentException(const sk::util::String& message, const sk::util::Strings& details)
  : sk::util::Exception(sk::util::Strings("Illegal argument") << message << details)
{
}

const sk::util::Class
sk::util::IllegalArgumentException::
getClass() const
{
  return sk::util::Class(__className);
}
