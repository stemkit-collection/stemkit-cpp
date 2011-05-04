/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "SocketInputStream.h"

sk::net::win32::SocketInputStream::
SocketInputStream(int fd)
  : _descriptor(fd)
{
}

sk::net::win32::SocketInputStream::
SocketInputStream(const sk::io::FileDescriptor& descriptor)
  : _descriptor(descriptor)
{
}

sk::net::win32::SocketInputStream::
SocketInputStream(const sk::net::win32::SocketInputStream& other)
  : _descriptor(other._descriptor)
{
}

sk::net::win32::SocketInputStream::
~SocketInputStream()
{
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
  _descriptor.close();
}

int 
sk::net::win32::SocketInputStream::
read(char* buffer, int offset, int length)
{
  return filterReadEvents(_descriptor.read(buffer, offset, length));
}

const sk::io::FileDescriptor&
sk::net::win32::SocketInputStream::
getFileDescriptor() const
{
  return _descriptor;
}

void
sk::net::win32::SocketInputStream::
inheritable(bool state)
{
  return _descriptor.inheritable(state);
}

const sk::util::String
sk::net::win32::SocketInputStream::
inspect() const
{
  return "<" + getClass().getName() + ": " + _descriptor.inspect() + ">";
}
