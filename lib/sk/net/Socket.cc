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
#include <sk/util/String.h>

#include <sk/net/Socket.h>

static const char* __className("sk::net::Socket");

sk::net::Socket::
Socket()
{
}

sk::net::Socket::
~Socket()
{
}

const sk::util::Class
sk::net::Socket::
getClass() const
{
  return sk::util::Class(__className);
}
