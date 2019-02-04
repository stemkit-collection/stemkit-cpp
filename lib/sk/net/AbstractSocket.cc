/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
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
#include <sk/net/AbstractSocket.h>

static const sk::util::String __className("sk::net::AbstractSocket");

sk::net::AbstractSocket::
AbstractSocket(sk::net::DirectedSocket* directedSocket)
  : _directedSocketHolder(directedSocket)
{
}

sk::net::AbstractSocket::
~AbstractSocket()
{
}

const sk::util::Class
sk::net::AbstractSocket::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::net::AbstractSocket::
close()
{
  _directedSocketHolder.clear();
}

const sk::net::DirectedSocket&
sk::net::AbstractSocket::
directedSocket() const
{
  return _directedSocketHolder.get();
}

const sk::net::InetSocketAddress& 
sk::net::AbstractSocket::
localEndpoint() const
{
  if(_localEndpointHolder.isEmpty() == true) {
    _localEndpointHolder.set(_directedSocketHolder.get().localEndpoint());
  }
  return _localEndpointHolder.get();
}

const sk::net::InetAddress& 
sk::net::AbstractSocket::
localAddress() const
{
  return localEndpoint().getAddress();
}

const uint16_t
sk::net::AbstractSocket::
localPort() const
{
  return localEndpoint().getPort();
}

const sk::net::InetSocketAddress& 
sk::net::AbstractSocket::
endpoint() const
{
  if(_endpointHolder.isEmpty() == true) {
    _endpointHolder.set(sk::net::InetSocketAddress(_directedSocketHolder.get().address(), port()));
  }
  return _endpointHolder.get();
}

const sk::net::InetAddress& 
sk::net::AbstractSocket::
address() const
{
  return endpoint().getAddress();
}

const uint16_t
sk::net::AbstractSocket::
port() const
{
  return _directedSocketHolder.get().port();
}

void
sk::net::AbstractSocket::
setReuseAddress(bool state)
{
  _directedSocketHolder.getMutable().setReuseAddress(state);
}
