/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "SocketOutputStream.h"

sk::net::win32::SocketOutputStream::
SocketOutputStream(int fd)
  : _descriptor(fd)
{
}

sk::net::win32::SocketOutputStream::
SocketOutputStream(const sk::io::FileDescriptor& descriptor)
  : _descriptor(descriptor)
{
}

sk::net::win32::SocketOutputStream::
SocketOutputStream(const sk::net::win32::SocketOutputStream& other)
  : _descriptor(other._descriptor)
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
  _descriptor.close();
}

int
sk::net::win32::SocketOutputStream::
write(const char* buffer, int offset, int length)
{
  return _descriptor.write(buffer, offset, length);
}

void
sk::net::win32::SocketOutputStream::
inheritable(bool state)
{
  _descriptor.inheritable(state);
}

const sk::io::FileDescriptor&
sk::net::win32::SocketOutputStream::
getFileDescriptor() const
{
  return _descriptor;
}

const sk::util::String
sk::net::win32::SocketOutputStream::
inspect() const
{
  return "<" + getClass().getName() + ": " + _descriptor.inspect() + ">";
}
