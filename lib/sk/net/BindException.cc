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

#include <sk/net/BindException.h>

static const sk::util::String __className("sk::net::BindException");

sk::net::BindException::
BindException(const sk::util::String& address, const uint16_t port)
  : sk::net::SocketException("bind", sk::util::Strings(address) << sk::util::String::valueOf(port)), _address(address), _port(port) 
{
}

sk::net::BindException::
~BindException() throw()
{
}

const sk::util::Class
sk::net::BindException::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::net::BindException::
getAddress() const
{
  return _address;
}

const uint16_t
sk::net::BindException::
getPort() const
{
  return _port;
}
