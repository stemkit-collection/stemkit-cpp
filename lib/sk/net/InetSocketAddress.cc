/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/net/InetSocketAddress.h>

static const char* __className("sk::net::InetSocketAddress");

sk::net::InetSocketAddress::
InetSocketAddress(const sk::net::InetAddress& address, uint16_t port)
  : _port(port) 
{
}

sk::net::InetSocketAddress::
InetSocketAddress(const sk::util::String& hostname, uint16_t port)
  : _port(port) 
{
}

sk::net::InetSocketAddress::
InetSocketAddress(uint16_t port)
  : _port(port) 
{
}

sk::net::InetSocketAddress::
~InetSocketAddress()
{
}

const sk::util::Class
sk::net::InetSocketAddress::
getClass() const
{
  return sk::util::Class(__className);
}

uint16_t 
sk::net::InetSocketAddress::
getPort() const
{
  return _port;
}
