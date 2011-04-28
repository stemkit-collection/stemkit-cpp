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
#include <sk/util/IllegalStateException.h>

#include <sk/net/ServerSocket.h>
#include <sk/net/InetSocketAddress.h>

static const char* __className("sk::net::ServerSocket");

sk::net::ServerSocket::
ServerSocket()
  : _bound(false)
{
}

sk::net::ServerSocket::
ServerSocket(int port)
  : _bound(false)
{
}

sk::net::ServerSocket::
ServerSocket(int port, int backlog)
  : _bound(false)
{
}

sk::net::ServerSocket::
ServerSocket(int port, int backlog, const sk::net::InetAddress& bindAddress)
  : _bound(false)
{
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
  if(_bound == false) {
    return "<unbound server socket>";
  }
  return _endpointHolder.get().toString();
}

sk::net::Socket 
sk::net::ServerSocket::
accept()
{
  ensureBound();
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::net::ServerSocket::
bind(const InetSocketAddress& endpoint)
{
  bind(endpoint, 0);
}

void 
sk::net::ServerSocket::
bind(const InetSocketAddress& endpoint, int backlog)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::net::ServerSocket::
isBound() const
{
  return _bound;
}

void 
sk::net::ServerSocket::
close()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::net::ServerSocket::
ensureBound() const
{
  if(_bound == false) {
    throw sk::util::IllegalStateException("Server socket not bound");
  }
}

int 
sk::net::ServerSocket::
getPort() const
{
  ensureBound();
  return _endpointHolder.get().getPort();
}

const sk::net::InetSocketAddress& 
sk::net::ServerSocket::
getSocketAddress() const
{
  ensureBound();
  return _endpointHolder.get();
}

const sk::net::InetAddress& 
sk::net::ServerSocket::
getInetAddress() const
{
  return getSocketAddress().getAddress();
}

bool 
sk::net::ServerSocket::
getReuseAddress() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::net::ServerSocket::
setReuseAddress(bool state)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::net::ServerSocket::
getReceiveBufferSize() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::net::ServerSocket::
setReceiveBufferSize(int size)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::net::ServerSocket::
getSoTimeout() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::net::ServerSocket::
setSoTimeout(int timeout)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
