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
#include <sk/util/IllegalStateException.h>

#include <sk/net/ip4/InetAddress.h>

static const sk::util::String __className("sk::net::ip4::InetAddress");

sk::net::ip4::InetAddress::
InetAddress(const sk::util::bytes& components)
  : sk::net::InetAddress(components)
{
  if(components.size() != 4) {
    throw sk::util::IllegalStateException("Wrong IPV4 address");
  }
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

const sk::util::String 
sk::net::ip4::InetAddress::
getHostAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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

