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
#include <sk/util/String.h>

#include <sk/net/SocketException.h>

static const sk::util::String __className("sk::net::SocketException");

sk::net::SocketException::
SocketException(const sk::util::String& message)
  : sk::rt::SystemException(message)
{
}

sk::net::SocketException::
SocketException(const sk::util::String& message, const sk::util::Strings& details)
  : sk::rt::SystemException(message, details)
{
}

const sk::util::Class
sk::net::SocketException::
getClass() const
{
  return sk::util::Class(__className);
}
