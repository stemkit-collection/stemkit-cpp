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
#include <sk/util/Strings.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/rt/SystemException.h>
#include <sk/net/ip4/InetAddress.h>

#include "DirectedSocket.h"

static const sk::util::String __className("sk::net::ip4::DirectedSocket");

namespace {
  const sockaddr_in makeAddr(uint32_t number, uint16_t port) {
    sockaddr_in addr = { 0 };

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(number);

    return addr;
  }
}

sk::net::ip4::DirectedSocket::
DirectedSocket(uint32_t number, uint16_t port)
  : _address(makeAddr(number, port)), _socket(::socket(PF_INET, SOCK_STREAM, 0))
{
  if(_socket == -1) {
    throw sk::rt::SystemException("socket()");
  }
}

sk::net::ip4::DirectedSocket::
DirectedSocket(const struct sockaddr_in address, int socket)
  : _address(address), _socket(socket)
{
}

sk::net::ip4::DirectedSocket::
~DirectedSocket()
{
  if(_socket >= 0) {
    ::close(_socket);
  }
}

const sk::util::Class
sk::net::ip4::DirectedSocket::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::net::ip4::DirectedSocket::
bind() const
{
  if(::bind(_socket, reinterpret_cast<const sockaddr*>(&_address), sizeof(_address)) == -1) {
    throw sk::rt::SystemException("bind()");
  }
}

void 
sk::net::ip4::DirectedSocket::
listen(int backlog) const
{
  if(::listen(_socket, backlog) == -1) {
    throw sk::rt::SystemException("listen()");
  }
}

void 
sk::net::ip4::DirectedSocket::
connect() const
{
  if(::connect(_socket, reinterpret_cast<const sockaddr*>(&_address), sizeof(_address)) == -1) {
    throw sk::rt::SystemException("connect()");
  }
}

sk::net::DirectedSocket* 
sk::net::ip4::DirectedSocket::
accept() const
{
  struct sockaddr_in addr;
  socklen_t size;

  int socket = ::accept(_socket, reinterpret_cast<sockaddr*>(&addr), &size);
  if(socket == -1) {
    throw sk::rt::SystemException("accept()");
  }
  if(size != sizeof(addr)) {
    throw sk::util::IllegalStateException("accept()", "sockaddr_in size mismatch");
  }
  return new sk::net::ip4::DirectedSocket(addr, socket);
}

uint16_t
sk::net::ip4::DirectedSocket::
getPort() const
{
  return ntohs(_address.sin_port);
}

sk::net::InetAddress&
sk::net::ip4::DirectedSocket::
getAddress() const
{
  return sk::net::InetAddress::getByAddress(sk::net::ip4::InetAddress::toComponents(ntohl(_address.sin_addr.s_addr)));
}

sk::io::InputStream&
sk::net::ip4::DirectedSocket::
inputStream() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::OutputStream&
sk::net::ip4::DirectedSocket::
outputStream() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
