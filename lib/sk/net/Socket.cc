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
Socket(const sk::net::InetSocketAddress& endpoint)
  : _directedSocketHolder(endpoint.getAddress().makeDirectedSocket(endpoint.getPort()))
{
  _directedSocketHolder.get().connect();
}

sk::net::Socket::
Socket(const sk::net::InetAddress& address, int port)
  : _directedSocketHolder(address.makeDirectedSocket(port))
{
  _directedSocketHolder.get().connect();
}

sk::net::Socket::
Socket(const sk::util::String& host, int port)
  : _directedSocketHolder(sk::net::InetAddress::getByName(host).makeDirectedSocket(port))
{
  _directedSocketHolder.get().connect();
}

sk::net::Socket::
Socket(sk::net::DirectedSocket* directedSocket)
  : _directedSocketHolder(directedSocket)
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

const sk::net::InetSocketAddress& 
sk::net::Socket::
localEndpoint() const
{
  if(_localEndpointHolder.isEmpty() == true) {
    _localEndpointHolder.set(_directedSocketHolder.get().localEndpoint());
  }
  return _localEndpointHolder.get();
}

const sk::net::InetAddress& 
sk::net::Socket::
localAddress() const
{
  return localEndpoint().getAddress();
}

const uint16_t 
sk::net::Socket::
localPort() const
{
  return localEndpoint().getPort();
}

const sk::net::InetSocketAddress& 
sk::net::Socket::
endpoint() const
{
  if(_endpointHolder.isEmpty() == true) {
    _endpointHolder.set(sk::net::InetSocketAddress(_directedSocketHolder.get().address(), port()));
  }
  return _endpointHolder.get();
}

const sk::net::InetAddress& 
sk::net::Socket::
address() const
{
  return endpoint().getAddress();
}

const uint16_t 
sk::net::Socket::
port() const
{
  return _directedSocketHolder.get().port();
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
}
