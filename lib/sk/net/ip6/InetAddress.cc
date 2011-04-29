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

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

static const sk::util::String __className("sk::net::ip6::InetAddress");

namespace {
  const sk::util::bytes& figure_address_components(const sk::util::String& name, const struct addrinfo& info) {
    if(info.ai_family != AF_INET6) {
      throw sk::util::IllegalStateException("Wrong IPv6 address family", sk::util::Strings(sk::util::String::valueOf(info.ai_family)) << name);
    }
    if(info.ai_addrlen != sizeof(sockaddr_in6)) {
      throw sk::util::IllegalStateException("Wrong IPv6 address length", sk::util::Strings(sk::util::String::valueOf(info.ai_addrlen)) << name);
    }
    throw sk::util::UnsupportedOperationException("IPv6 resolution", name);
  }
}

sk::net::ip6::InetAddress::
InetAddress(const sk::util::String& name, const struct addrinfo& info)
  : sk::net::InetAddress(figure_address_components(name, info))
{
}

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
resolveHostName() const
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
makeDirectedSocket(uint16_t port) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
