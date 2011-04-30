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
#include <sk/net/ServerSocket.h>

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::ServerSocket");

sk::net::ServerSocket::
ServerSocket(const uint16_t port)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(port).makeDirectedSocket())
{
  setup(0);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(port).makeDirectedSocket())
{
  setup(backlog);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog, const sk::net::InetAddress& bindAddress)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(bindAddress, port).makeDirectedSocket())
{
  setup(backlog);
}

sk::net::ServerSocket::
~ServerSocket()
{
}

const sk::util::Class
sk::net::ServerSocket::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::net::ServerSocket::
toString() const
{
  return endpoint().toString();
}

void 
sk::net::ServerSocket::
setup(const int backlog)
{
  const sk::net::DirectedSocket& socket = directedSocket();

  socket.bind();
  socket.listen(backlog > 0 ? backlog : 5);
}

sk::net::Socket 
sk::net::ServerSocket::
accept()
{
  return sk::net::Socket(directedSocket().accept());
}
