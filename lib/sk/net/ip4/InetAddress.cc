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
  union {
    uint8_t c[4];
    uint32_t number;
  } data;

  data.c[0] = components[0];
  data.c[1] = components[1];
  data.c[2] = components[2];
  data.c[3] = components[3];

  return toHostOrder(data.number);
}

const sk::util::bytes
sk::net::ip4::InetAddress::
toComponents(uint32_t number)
{
  union {
    uint8_t c[4];
    uint32_t number;
  } data;

  data.number = toNetworkOrder(number);
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

sk::net::InetAddress&
sk::net::ip4::InetAddress::
getLoopbackAddress()
{
  return sk::net::InetAddress::getByAddress(sk::util::bytes(127) << 0 << 0 << 1);
}

sk::net::InetAddress&
sk::net::ip4::InetAddress::
getAnyLocalAddress()
{
  return sk::net::InetAddress::getByAddress(sk::util::bytes(0) << 0 << 0 << 0);
}
