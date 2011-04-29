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
#include <sk/util/Holder.cxx>

#include <sk/net/Socket.h>
#include <sk/net/InetAddress.h>

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::Socket");

sk::net::Socket::
Socket(sk::net::DirectedSocket* directedSocket, const sk::net::InetSocketAddress& localSocketAddress)
  : _directedSocketHolder(directedSocket), _localEndpointHolder(localSocketAddress)
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

uint16_t 
sk::net::Socket::
getLocalPort() const
{
  return _localEndpointHolder.get().getPort();
}

const sk::net::InetAddress& 
sk::net::Socket::
getLocalAddress() const
{
  return _localEndpointHolder.get().getAddress();
}

uint16_t 
sk::net::Socket::
getRemotePort() const
{
  return _directedSocketHolder.get().getPort();
}

const sk::net::InetAddress& 
sk::net::Socket::
getRemoteAddress() const
{
  return _directedSocketHolder.get().getAddress();
}

sk::io::InputStream& 
sk::net::Socket::
inputStream() const
{
  return _directedSocketHolder.get().inputStream();
}

sk::io::OutputStream& 
sk::net::Socket::
outputStream() const
{
  return _directedSocketHolder.get().outputStream();
}

void 
sk::net::Socket::
close()
{
  _directedSocketHolder.clear();
  _localEndpointHolder.clear();
}
