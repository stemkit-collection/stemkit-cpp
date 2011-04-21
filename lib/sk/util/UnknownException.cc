/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/Strings.h>

#include <sk/util/UnknownException.h>

static sk::util::String __defaultMessage("\?\?\?");

sk::util::UnknownException::
UnknownException(const sk::util::String& label)
  : sk::util::Exception(sk::util::Strings(label) << __defaultMessage)
{
}

sk::util::UnknownException::
UnknownException()
  : sk::util::Exception(__defaultMessage)
{
}

const sk::util::Class
sk::util::UnknownException::
getClass() const
{
  return sk::util::Class("<UNKNOWN>");
}
