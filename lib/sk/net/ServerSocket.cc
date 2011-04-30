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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/net/ServerSocket.h>
#include <sk/net/InetSocketAddress.h>
#include <sk/net/InetAddress.h>

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::ServerSocket");

sk::net::ServerSocket::
ServerSocket(const uint16_t port)
  : _socketAddressHolder(new sk::net::InetSocketAddress(port)), 
    _socketHolder(_socketAddressHolder.get().makeDirectedSocket())
{
  setup(0);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog)
  : _socketAddressHolder(new sk::net::InetSocketAddress(port)), 
    _socketHolder(_socketAddressHolder.get().makeDirectedSocket())
{
  setup(backlog);
}

sk::net::ServerSocket::
ServerSocket(const uint16_t port, const int backlog, const sk::net::InetAddress& bindAddress)
  : _socketAddressHolder(new sk::net::InetSocketAddress(bindAddress, port)),
    _socketHolder(_socketAddressHolder.get().makeDirectedSocket())
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
  return _socketAddressHolder.get().toString();
}

void 
sk::net::ServerSocket::
setup(const int backlog)
{
  const sk::net::DirectedSocket& socket = _socketHolder.get();

  socket.bind();
  socket.listen(backlog > 0 ? backlog : 5);
}

sk::net::Socket 
sk::net::ServerSocket::
accept()
{
  return sk::net::Socket(_socketHolder.get().accept());
}

void
sk::net::ServerSocket::
close()
{
  _socketHolder.clear();
  _socketAddressHolder.clear();
}

const uint16_t 
sk::net::ServerSocket::
getPort() const
{
  return _socketAddressHolder.get().getPort();
}

const sk::net::InetSocketAddress& 
sk::net::ServerSocket::
getSocketAddress() const
{
  return _socketAddressHolder.get();
}

const sk::net::InetAddress& 
sk::net::ServerSocket::
getInetAddress() const
{
  return getSocketAddress().getAddress();
}
