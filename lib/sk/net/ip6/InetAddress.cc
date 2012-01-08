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
#include <sk/util/Strings.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/net/ip6/InetAddress.h>
#include <sk/net/UnknownHostException.h>

static const sk::util::String __className("sk::net::ip6::InetAddress");

sk::net::ip6::InetAddress::
InetAddress(const sk::util::bytes& components)
  : sk::net::InetAddress(components)
{
  if(components.size() != 16) {
    throw sk::net::UnknownHostException("Wrong IPv6 address", components.inspect());
  }
}

sk::net::ip6::InetAddress::
~InetAddress()
{
}

const sk::util::Class
sk::net::ip6::InetAddress::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::net::ip6::InetAddress::
getHostAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::net::ip6::InetAddress::
lookupHostName() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::net::ip6::InetAddress::
isLoopbackAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::net::ip6::InetAddress::
isAnyLocalAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::net::ip6::InetAddress::
isSiteLocalAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::net::ip6::InetAddress::
isMulticastAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::net::DirectedSocket*
sk::net::ip6::InetAddress::
directedStreamSocket(const uint16_t port) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::net::DirectedSocket*
sk::net::ip6::InetAddress::
directedDatagramSocket(const uint16_t port) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
