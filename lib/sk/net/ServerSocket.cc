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

#include <sk/io/IOException.h>
#include <sk/rt/Actions.h>
#include <sk/rt/SystemException.h>

#include <sk/net/ServerSocket.h>
#include <sk/net/InetSocketAddress.h>
#include <sk/net/InetAddress.h>

#include <sys/socket.h>

static const char* __className("sk::net::ServerSocket");

sk::net::ServerSocket::
ServerSocket()
  : _backlog(0), _socket(-1)
{
}

sk::net::ServerSocket::
ServerSocket(int port)
{
  bind(sk::net::InetSocketAddress(port));
}

sk::net::ServerSocket::
ServerSocket(int port, int backlog)
{
  bind(sk::net::InetSocketAddress(port), backlog);
}

sk::net::ServerSocket::
ServerSocket(int port, int backlog, const sk::net::InetAddress& bindAddress)
{
  bind(sk::net::InetSocketAddress(bindAddress, port), backlog);
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
  if(isBound() == false) {
    return "<unbound server socket>";
  }
  return _endpointHolder.get().toString();
}

int 
sk::net::ServerSocket::
getBacklog() const
{
  return _backlog > 0 ? _backlog : 10;
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
  if(isBound() == true) {
    throw sk::io::IOException(SK_METHOD);
  }
  sk::rt::Actions undo(true);

  _backlog = backlog;
  _endpointHolder.set(endpoint);

  _socket = ::socket(PF_INET, SOCK_STREAM, 0);
  if(_socket == -1) {
    throw sk::rt::SystemException("socket()");
  }
  undo.add("reset", *this, &sk::net::ServerSocket::close);

  if(::bind(_socket, 0, 0) == -1) {
    throw sk::rt::SystemException("bind()");
  }
  if(::listen(_socket, getBacklog()) == -1) {
    throw sk::rt::SystemException("listen()");
  }
  undo.clear();
}

bool 
sk::net::ServerSocket::
isBound() const
{
  return _endpointHolder.isEmpty() == false;
}

void 
sk::net::ServerSocket::
close()
{
  if(_socket != -1) {
    ::close(_socket);
    _socket = -1;
  }
  _endpointHolder.clear();
}

void
sk::net::ServerSocket::
ensureBound() const
{
  if(isBound() == false) {
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
