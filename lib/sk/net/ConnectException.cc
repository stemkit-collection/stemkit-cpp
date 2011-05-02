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

#include <sk/net/ConnectException.h>

static const sk::util::String __className("sk::net::ConnectException");

sk::net::ConnectException::
ConnectException(const sk::util::String& message, const sk::util::String& host, const uint16_t port)
  : sk::net::SocketException("connect", sk::util::Strings(message) << host << sk::util::String::valueOf(port)), _host(host), _port(port)
{
}

sk::net::ConnectException::
ConnectException(const sk::util::String& host, const uint16_t port)
  : sk::net::SocketException("connect", sk::util::Strings(host) << sk::util::String::valueOf(port)), _host(host), _port(port)
{
}

sk::net::ConnectException::
~ConnectException() throw()
{
}

const sk::util::Class
sk::net::ConnectException::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::net::ConnectException::
getHost() const
{
  return _host;
}

const uint16_t
sk::net::ConnectException::
getPort() const
{
  return _port;
}
