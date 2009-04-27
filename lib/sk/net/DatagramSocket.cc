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

#include <sk/net/DatagramSocket.h>

static const char* __className("sk::net::DatagramSocket");

sk::net::DatagramSocket::
DatagramSocket()
{
}

sk::net::DatagramSocket::
~DatagramSocket()
{
}

const sk::util::Class
sk::net::DatagramSocket::
getClass() const
{
  return sk::util::Class(__className);
}