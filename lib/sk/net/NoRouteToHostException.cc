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

#include <sk/net/NoRouteToHostException.h>

static const sk::util::String __className("sk::net::NoRouteToHostException");

sk::net::NoRouteToHostException::
NoRouteToHostException(const sk::util::String& host, const uint16_t port)
  : sk::net::ConnectException(host, port)
{
}

const sk::util::Class
sk::net::NoRouteToHostException::
getClass() const
{
  return sk::util::Class(__className);
}
