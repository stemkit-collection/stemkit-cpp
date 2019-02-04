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
#include <sk/io/EOFException.h>

#include "SocketInputStream.h"

sk::net::win32::SocketInputStream::
SocketInputStream(const SOCKET socket)
  : _socket(socket)
{
}

sk::net::win32::SocketInputStream::
SocketInputStream(const sk::net::win32::SocketInputStream& other)
  : _socket(other._socket)
{
}

sk::net::win32::SocketInputStream::
~SocketInputStream()
{
  close();
}

sk::util::Object*
sk::net::win32::SocketInputStream::
clone() const
{
  return new sk::net::win32::SocketInputStream(*this);
}

const sk::util::Class
sk::net::win32::SocketInputStream::
getClass() const
{
  return sk::util::Class("sk::net::win32::SocketInputStream");
}

void 
sk::net::win32::SocketInputStream::
close()
{
  ::closesocket(_socket);
  _socket = INVALID_SOCKET;
}

int 
sk::net::win32::SocketInputStream::
read(char* buffer, int offset, int length)
{
  if(offset < 0) {
    offset = 0;
  }
  if(length < 0) {
    length = 0;
  }
  int n = ::recv(_socket, buffer + offset, length, 0);
  if(n == SOCKET_ERROR) {
    throw sk::rt::SystemException("recv()");
  }
  if(n == 0) {
    throw sk::io::EOFException();
  }
  return n;
}

void
sk::net::win32::SocketInputStream::
inheritable(bool state)
{
}

const sk::util::String
sk::net::win32::SocketInputStream::
inspect() const
{
  return "<" + getClass().getName() + ": " + sk::util::String::valueOf(_socket) + ">";
}
