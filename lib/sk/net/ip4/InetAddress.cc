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
#include <sk/rt/SystemException.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/UnknownHostException.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::ip4::InetAddress");

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

sk::net::ip4::InetAddress::
InetAddress(const sk::util::bytes& components)
  : sk::net::InetAddress(components), _number(toNumber(components))
{
}

sk::net::ip4::InetAddress::
~InetAddress()
{
}

const sk::util::Class
sk::net::ip4::InetAddress::
getClass() const
{
  return sk::util::Class(__className);
}

sk::util::Object*
sk::net::ip4::InetAddress::
clone() const
{
  return new sk::net::ip4::InetAddress(*this);
}

uint32_t
sk::net::ip4::InetAddress::
toNumber(const sk::util::bytes& components)
{
  if(components.size() != 4) {
    throw sk::net::UnknownHostException("Wrong IPv4 address", toString(components));
  }
  uint32_t result = 0;
  for(sk::util::bytes::const_iterator iterator = components.begin(); iterator != components.end(); ++iterator) {
    result = (result << 8) | *iterator;
  }
  return ntohl(result);
}

const sk::util::bytes
sk::net::ip4::InetAddress::
toComponents(uint32_t number)
{
  union {
    uint8_t c[4];
    uint32_t number;
  } data;
  data.number = htonl(number);

  return sk::util::bytes(data.c[0]) << data.c[1] << data.c[2] << data.c[3];
}

const sk::util::String
sk::net::ip4::InetAddress::
toString(const sk::util::bytes& components)
{
  return components.join(".");
}

const sk::util::String 
sk::net::ip4::InetAddress::
getHostAddress() const
{
  return toString(getAddress());
}

const sk::util::String 
sk::net::ip4::InetAddress::
resolveHostName() const
{
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = _number;

  char hostname[NI_MAXHOST];
  int status = getnameinfo(reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr), hostname, sizeof(hostname), 0, 0, NI_NAMEREQD);
  if(status == 0) {
    return hostname;
  }
  throw sk::net::UnknownHostException(gai_strerror(status), getHostAddress());
}

bool 
sk::net::ip4::InetAddress::
isLoopbackAddress() const
{
  return getAddress()[0] == 0x7F;
}

bool 
sk::net::ip4::InetAddress::
isAnyLocalAddress() const
{
  return _number == 0;
}

bool 
sk::net::ip4::InetAddress::
isSiteLocalAddress() const
{
  const sk::util::bytes& addr = getAddress();
  // 10.0.0.0/8
  if (addr[0] == 0x0A) {
    return true;
  }

  // 172.16.0.0/12
  if (addr[0] == 0xAC && (addr[1] & 0xF0) == 0x01) {
    return true;
  }

  // 192.168.0.0/16
  if (addr[0] == 0xC0 && addr[1] == 0xA8) {
    return true;
  }

  return false;
}

bool 
sk::net::ip4::InetAddress::
isMulticastAddress() const
{
  return (getAddress()[0] & 0xF0) == 0xE0;
}

const sk::net::InetAddress&
sk::net::ip4::InetAddress::
getLoopbackAddress()
{
  return sk::net::InetAddress::getByAddress(sk::util::bytes(127) << 0 << 0 << 1);
}

const sk::net::InetAddress&
sk::net::ip4::InetAddress::
getAnyLocalAddress()
{
  return sk::net::InetAddress::getByAddress(sk::util::bytes(0) << 0 << 0 << 0);
}

sk::net::DirectedSocket*
sk::net::ip4::InetAddress::
makeDirectedSocket(uint16_t port) const
{
  return new sk::net::ip4::DirectedSocket(_number, port);
}
