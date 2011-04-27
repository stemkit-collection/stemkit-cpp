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
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/net/ip4/InetAddress.h>
#include <sk/net/UnknownHostException.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

static const sk::util::String __className("sk::net::ip4::InetAddress");

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

uint32_t
sk::net::ip4::InetAddress::
toNumber(const sk::util::bytes& components)
{
  if(components.size() != 4) {
    throw sk::net::UnknownHostException("Wrong IPV4 address", toString(components));
  }
  uint32_t result = 0;
  for(sk::util::bytes::const_iterator iterator = components.begin(); iterator != components.end(); ++iterator) {
    result = (result << 8) | *iterator;
  }
  return ntohl(result);
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::net::ip4::InetAddress::
isAnyLocalAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::net::ip4::InetAddress::
isMulticastAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

