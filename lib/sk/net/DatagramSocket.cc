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

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::DatagramSocket");

sk::net::DatagramSocket::
DatagramSocket()
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(0).directedDatagramSocket())
{
  directedSocket().bind();
}

sk::net::DatagramSocket::
DatagramSocket(const uint16_t port)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(port).directedDatagramSocket())
{
  directedSocket().bind();
}

sk::net::DatagramSocket::
DatagramSocket(const uint16_t port, const sk::net::InetAddress& address)
  : sk::net::AbstractSocket(sk::net::InetSocketAddress(address, port).directedDatagramSocket())
{
  directedSocket().bind();
}

sk::net::DatagramSocket::
DatagramSocket(const sk::net::InetSocketAddress& endpoint)
  : sk::net::AbstractSocket(endpoint.directedDatagramSocket())
{
  directedSocket().bind();
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

void
sk::net::DatagramSocket::
receive(sk::net::DatagramPacket& packet)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::net::DatagramSocket::
send(const sk::net::DatagramPacket& packet)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
