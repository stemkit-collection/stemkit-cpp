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

#include <sk/net/ip4/Address.h>

sk::net::ip4::Address::
Address()
{
}

sk::net::ip4::Address::
~Address()
{
}

const sk::util::Class
sk::net::ip4::Address::
getClass() const
{
  return sk::util::Class("sk::net::ip4::Address");
}
