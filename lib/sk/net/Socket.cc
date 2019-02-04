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

static const sk::util::String __className("sk::net::Socket");

sk::net::Socket::
Socket(const sk::net::InetSocketAddress& endpoint)
  : sk::net::AbstractSocket(endpoint.getAddress().directedStreamSocket(endpoint.getPort()))
{
  directedSocket().connect();
}

sk::net::Socket::
Socket(const sk::net::InetAddress& address, const uint16_t port)
  : sk::net::AbstractSocket(address.directedStreamSocket(port))
{
  directedSocket().connect();
}

sk::net::Socket::
Socket(const sk::util::String& host, const uint16_t port)
  : sk::net::AbstractSocket(sk::net::InetAddress::getByName(host).directedStreamSocket(port))
{
  directedSocket().connect();
}

sk::net::Socket::
Socket(sk::net::DirectedSocket* directedSocket)
  : sk::net::AbstractSocket(directedSocket)
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

sk::io::InputStream& 
sk::net::Socket::
inputStream() const
{
  return directedSocket().inputStream();
}

sk::io::OutputStream& 
sk::net::Socket::
outputStream() const
{
  return directedSocket().outputStream();
}
