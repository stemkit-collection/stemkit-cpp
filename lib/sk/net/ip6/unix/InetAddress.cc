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

