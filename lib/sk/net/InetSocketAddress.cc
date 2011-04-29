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
#include <sk/util/Holder.cxx>

#include <sk/net/InetSocketAddress.h>
#include <sk/net/ip4/InetAddress.h>

static const char* __className("sk::net::InetSocketAddress");

sk::net::InetSocketAddress::
InetSocketAddress(const sk::net::InetAddress& address, uint16_t port)
  : _addressHolder(address), _port(port) 
{
}

sk::net::InetSocketAddress::
InetSocketAddress(const sk::util::String& hostname, uint16_t port)
  : _addressHolder(sk::net::InetAddress::getByName(hostname)), _port(port) 
{
}

sk::net::InetSocketAddress::
InetSocketAddress(uint16_t port)
  : _addressHolder(sk::net::ip4::InetAddress::getAnyLocalAddress()), _port(port) 
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

const sk::util::String
sk::net::InetSocketAddress::
toString() const
{
  return _addressHolder.get().toString() + ':' + sk::util::String::valueOf(_port);
}

uint16_t 
sk::net::InetSocketAddress::
getPort() const
{
  return _port;
}

const sk::net::InetAddress&
sk::net::InetSocketAddress::
getAddress() const 
{
  return _addressHolder.get();
}

const sk::util::String
sk::net::InetSocketAddress::
getHostName() const
{
  return _addressHolder.get().getHostName();
}

bool
sk::net::InetSocketAddress::
isResolved() const 
{
  return _addressHolder.get().isResolved();
}

sk::net::DirectedSocket*
sk::net::InetSocketAddress::
makeDirectedSocket() const
{
  return getAddress().makeDirectedSocket(_port);
}
