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
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(port).directedStreamSocket())
{
  setup(0);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(port).directedStreamSocket())
{
  setup(backlog);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog, const sk::net::InetAddress& address)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(address, port).directedStreamSocket())
{
  setup(backlog);
}

sk::net::ServerSocket::
ServerSocket(const sk::net::InetSocketAddress& endpoint)
  : sk::net::AbstractSocket(endpoint.directedStreamSocket())
{
  setup(0);
}

sk::net::ServerSocket::
ServerSocket(const sk::net::InetSocketAddress& endpoint, const int backlog)
  : sk::net::AbstractSocket(endpoint.directedStreamSocket())
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
  _backlog = backlog;
  _bound = false;
}

sk::net::Socket 
sk::net::ServerSocket::
accept()
{
  const sk::net::DirectedSocket& socket = directedSocket();

  if(_bound == false) {
    socket.bind();
    socket.listen(_backlog > 0 ? _backlog : 5);

    _bound = true;
  }
  return sk::net::Socket(socket.accept());
}
