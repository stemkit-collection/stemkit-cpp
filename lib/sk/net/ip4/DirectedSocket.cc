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
#include <sk/util/Holder.hxx>

#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>

#include <sk/net/SocketException.h>
#include <sk/net/BindException.h>
#include <sk/net/ConnectException.h>
#include <sk/net/NoRouteToHostException.h>
#include <sk/net/ip4/InetAddress.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

#include "DirectedSocket.h"
#include <cerrno>

static const sk::util::String __className("sk::net::ip4::DirectedSocket");

namespace {
  const sockaddr_in makeAddr(const uint32_t number, const uint16_t port) {
    struct sockaddr_in addr = { 0 };

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(number);

    return addr;
  }
}

sk::net::ip4::DirectedSocket::
DirectedSocket(const uint32_t number, const uint16_t port, const int socket)
  : _address(makeAddr(number, port)), _socket(socket)
{
  if(_socket == -1) {
    throw sk::net::SocketException("socket()");
  }
}

sk::net::ip4::DirectedSocket::
DirectedSocket(const struct sockaddr_in& address, const int socket)
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

sk::net::DirectedSocket* 
sk::net::ip4::DirectedSocket::
streamSocket(const uint32_t number, const uint16_t port)
{
  return new sk::net::ip4::DirectedSocket(number, port, ::socket(PF_INET, SOCK_STREAM, 0));
}

sk::net::DirectedSocket* 
sk::net::ip4::DirectedSocket::
datagramSocket(const uint32_t number, const uint16_t port)
{
  return new sk::net::ip4::DirectedSocket(number, port, ::socket(PF_INET, SOCK_DGRAM, 0));
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
    if(errno == EADDRINUSE) {
      throw sk::net::BindException(port());
    }
    throw sk::net::SocketException("bind()");
  }
}

void 
sk::net::ip4::DirectedSocket::
listen(const int backlog) const
{
  if(::listen(_socket, backlog) == -1) {
    throw sk::net::SocketException("listen()");
  }
}

void 
sk::net::ip4::DirectedSocket::
connect() const
{
  if(::connect(_socket, reinterpret_cast<const sockaddr*>(&_address), sizeof(_address)) == -1) {
    if(errno == ECONNREFUSED) {
      throw sk::net::ConnectException(address().getHostName(), port());
    }
    if((errno == EHOSTUNREACH) || (errno == ENETUNREACH)) {
      throw sk::net::NoRouteToHostException(address().getHostName());
    }
    throw sk::net::SocketException("connect()");
  }
}

sk::net::DirectedSocket* 
sk::net::ip4::DirectedSocket::
accept() const
{
  struct sockaddr_in addr = { 0 };
  socklen_t size = sizeof(addr);

  const int socket = ::accept(_socket, reinterpret_cast<sockaddr*>(&addr), &size);
  if(socket == -1) {
    throw sk::net::SocketException("accept()");
  }
  if(size != sizeof(addr)) {
    throw sk::util::IllegalStateException("accept()", "sockaddr_in size mismatch");
  }
  return new sk::net::ip4::DirectedSocket(addr, socket);
}

void 
sk::net::ip4::DirectedSocket::
sendto(const std::vector<char>& data, const sk::net::InetAddress& address, const uint16_t port) const
{
  std::vector<char>::size_type amount = data.size();
  if(amount == 0) {
    return;
  }
  sockaddr_in addr = { 0 };
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(sk::net::ip4::InetAddress::toNumber(address.getAddress()));

  ssize_t n = ::sendto(_socket, &data[0], amount, 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
  if(n == -1) {
    throw sk::net::SocketException("sendto()");
  }
  if(n != amount) {
    throw sk::util::IllegalStateException("sendto()", sk::util::Strings("amount mismatch") << sk::util::String::valueOf(n) << sk::util::String::valueOf(amount));
  }
}

const sk::net::InetSocketAddress 
sk::net::ip4::DirectedSocket::
recvfrom(std::vector<char>& data) const
{
  sockaddr_in addr = { 0 };
  socklen_t size = sizeof(addr);

  ssize_t n = ::recvfrom(_socket, &data[0], data.size(), 0, reinterpret_cast<sockaddr*>(&addr), &size);
  if(n == -1) {
    throw sk::net::SocketException("recvfrom()");
  }
  if(size != sizeof(addr)) {
    throw sk::util::IllegalStateException("recvfrom()", "sockaddr_in size mismatch");
  }
  data.resize(n);

  const sk::util::bytes components = sk::net::ip4::InetAddress::toComponents(ntohl(addr.sin_addr.s_addr));
  return sk::net::InetSocketAddress(sk::net::InetAddress::getByAddress(components), ntohs(addr.sin_port));
}

const uint16_t
sk::net::ip4::DirectedSocket::
port() const
{
  return ntohs(_address.sin_port);
}

sk::net::InetAddress&
sk::net::ip4::DirectedSocket::
address() const
{
  return sk::net::InetAddress::getByAddress(sk::net::ip4::InetAddress::toComponents(ntohl(_address.sin_addr.s_addr)));
}

const sk::net::InetSocketAddress
sk::net::ip4::DirectedSocket::
localEndpoint() const
{
  struct sockaddr_in addr = { 0 };
  socklen_t size = sizeof(addr);

  if(::getsockname(_socket, reinterpret_cast<sockaddr*>(&addr), &size) == -1) {
    throw sk::net::SocketException("getsockname()");
  }
  if(size != sizeof(addr)) {
    throw sk::util::IllegalStateException("getsockname()", "sockaddr_in size mismatch");
  }
  const sk::util::bytes components = sk::net::ip4::InetAddress::toComponents(ntohl(addr.sin_addr.s_addr));
  return sk::net::InetSocketAddress(sk::net::InetAddress::getByAddress(components), ntohs(addr.sin_port));
}

sk::io::InputStream&
sk::net::ip4::DirectedSocket::
inputStream() const
{
  if(_inputStreamHolder.isEmpty() == true) {
    _inputStreamHolder.set(new sk::io::FileDescriptorInputStream(_socket));
  }
  return _inputStreamHolder.getMutable();
}

sk::io::OutputStream&
sk::net::ip4::DirectedSocket::
outputStream() const
{
  if(_outputStreamHolder.isEmpty() == true) {
    _outputStreamHolder.set(new sk::io::FileDescriptorOutputStream(_socket));
  }
  return _outputStreamHolder.getMutable();
}

void
sk::net::ip4::DirectedSocket::
setReuseAddress(bool state)
{
  int value = (state == true ? 1 : 0);
  if(::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1) {
    throw sk::net::SocketException("setsockopt()");
  }
}
