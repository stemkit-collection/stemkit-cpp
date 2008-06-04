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

#include <sk/net/ip4/Address.h>

sk::net::ip4::Address::
Address()
{
}

sk::net::ip4::Address::
Address(const Address& other)
{
}

sk::net::ip4::Address::
Address(uint32_t number)
{
}

sk::net::ip4::Address::
~Address()
{
}

const sk::net::ip4::Address
sk::net::ip4::Address::
number(uint32_t number) 
{
  return Address(number);
}

const sk::net::ip4::Address
sk::net::ip4::Address::
localhost()
{
  return Address("localhost");
}

const sk::util::Class
sk::net::ip4::Address::
getClass() const
{
  return sk::util::Class("sk::net::ip4::Address");
}

uint32_t
sk::net::ip4::Address::
number() const
{
  throw sk::util::UnsupportedOperationException("number()");
}

const sk::util::String
sk::net::ip4::Address::
hostname() const
{
  throw sk::util::UnsupportedOperationException("hostname()");
}

const sk::util::String
sk::net::ip4::Address::
ip() const
{
  throw sk::util::UnsupportedOperationException("ip()");
}
