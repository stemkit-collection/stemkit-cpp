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

#include <sk/net/UnknownHostException.h>

static const sk::util::String __className("sk::net::UnknownHostException");

sk::net::UnknownHostException::
UnknownHostException(const sk::util::String& hostid)
  : sk::util::Exception(sk::util::Strings("Unknown host") << hostid)
{
}

sk::net::UnknownHostException::
UnknownHostException(const sk::util::String& message, const sk::util::String& hostid)
  : sk::util::Exception(sk::util::Strings(message) << hostid)
{
}

const sk::util::Class
sk::net::UnknownHostException::
getClass() const
{
  return sk::util::Class(__className);
}
