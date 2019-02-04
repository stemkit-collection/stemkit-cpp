/*  vim: sw=2:
 *  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
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
#include <sk/util/IllegalStateException.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/UnknownHostException.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "DirectedSocket.h"

namespace {
  const sk::util::bytes figure_address_components(const sk::util::String& name, const struct addrinfo& info) {
    if(info.ai_family != AF_INET) {
      throw sk::util::IllegalStateException("Wrong IPv4 address family", sk::util::Strings(sk::util::String::valueOf(info.ai_family)) << name);
    }
    if(info.ai_addrlen != sizeof(sockaddr_in)) {
      throw sk::util::IllegalStateException("Wrong IPv4 address length", sk::util::Strings(sk::util::String::valueOf(info.ai_addrlen)) << name);
    }
    return sk::net::ip4::InetAddress::toComponents(ntohl(reinterpret_cast<struct sockaddr_in*>(info.ai_addr)->sin_addr.s_addr));
  }
}

sk::net::ip4::InetAddress::
InetAddress(const sk::util::String& name, const struct addrinfo& info)
  : sk::net::InetAddress(figure_address_components(name, info), name), _number(toNumber(getAddress()))
{
}

const uint32_t
sk::net::ip4::InetAddress::
toHostOrder(const uint32_t number)
{
  return ntohl(number);
}

const uint32_t
sk::net::ip4::InetAddress::
toNetworkOrder(const uint32_t number)
{
  return htonl(number);
}

const sk::util::String 
sk::net::ip4::InetAddress::
lookupHostName() const
{
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = ntohl(_number);

  char hostname[NI_MAXHOST];
  int status = getnameinfo(reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr), hostname, sizeof(hostname), 0, 0, NI_NAMEREQD);
  if(status == 0) {
    return hostname;
  }
  throw sk::net::UnknownHostException(gai_strerror(status), getHostAddress());
}

sk::net::DirectedSocket*
sk::net::ip4::InetAddress::
directedStreamSocket(const uint16_t port) const
{
  return sk::net::ip4::DirectedSocket::streamSocket(_number, port);
}

sk::net::DirectedSocket*
sk::net::ip4::InetAddress::
directedDatagramSocket(const uint16_t port) const
{
  return sk::net::ip4::DirectedSocket::datagramSocket(_number, port);
}
