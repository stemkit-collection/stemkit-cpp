/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/rt/SystemException.h>

#include "SocketOutputStream.h"

sk::net::win32::SocketOutputStream::
SocketOutputStream(const SOCKET socket)
  : _socket(socket)
{
}

sk::net::win32::SocketOutputStream::
SocketOutputStream(const sk::net::win32::SocketOutputStream& other)
  : _socket(other._socket)
{
}

sk::net::win32::SocketOutputStream::
~SocketOutputStream()
{
}

sk::util::Object*
sk::net::win32::SocketOutputStream::
clone() const
{
  return new sk::net::win32::SocketOutputStream(*this);
}

const sk::util::Class
sk::net::win32::SocketOutputStream::
getClass() const
{
  return sk::util::Class("sk::net::win32::SocketOutputStream");
}

void
sk::net::win32::SocketOutputStream::
close()
{
  ::closesocket(_socket);
  _socket = INVALID_SOCKET;
}

int
sk::net::win32::SocketOutputStream::
write(const char* buffer, int offset, int length)
{
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }
  int n = ::send(_socket, buffer + offset, length, 0);
  if(n == SOCKET_ERROR) {
    throw sk::rt::SystemException("send()");
  }
  return n;
}

void
sk::net::win32::SocketOutputStream::
inheritable(bool state)
{
}

const sk::util::String
sk::net::win32::SocketOutputStream::
inspect() const
{
  return "<" + getClass().getName() + ": " + sk::util::String::valueOf(_socket) + ">";
}
