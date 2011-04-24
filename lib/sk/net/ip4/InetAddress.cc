/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
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

sk::net::ip4::InetAddress::
InetAddress()
{
}

sk::net::ip4::InetAddress::
InetAddress(const InetAddress& /*TODO: other*/)
{
}

sk::net::ip4::InetAddress::
InetAddress(const sk::util::String& /*TODO: spec*/)
{
}

sk::net::ip4::InetAddress::
InetAddress(uint32_t /*TODO: number*/)
{
}

sk::net::ip4::InetAddress::
~InetAddress()
{
}

const sk::net::ip4::InetAddress
sk::net::ip4::InetAddress::
number(uint32_t number) 
{
  return InetAddress(number);
}

const sk::net::ip4::InetAddress
sk::net::ip4::InetAddress::
localhost()
{
  return InetAddress("localhost");
}

const sk::util::Class
sk::net::ip4::InetAddress::
getClass() const
{
  return sk::util::Class("sk::net::ip4::InetAddress");
}

uint32_t
sk::net::ip4::InetAddress::
number() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::net::ip4::InetAddress::
hostname() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::String
sk::net::ip4::InetAddress::
ip() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
