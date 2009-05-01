/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileDescriptorOutputStream.h>

sk::io::FileDescriptorOutputStream::
FileDescriptorOutputStream(int fd)
  : _descriptor(fd)
{
}

sk::io::FileDescriptorOutputStream::
FileDescriptorOutputStream(const sk::io::FileDescriptor& descriptor)
  : _descriptor(descriptor)
{
}

sk::io::FileDescriptorOutputStream::
FileDescriptorOutputStream(const sk::io::FileDescriptorOutputStream& other)
  : _descriptor(other._descriptor)
{
}

sk::io::FileDescriptorOutputStream::
~FileDescriptorOutputStream()
{
}

sk::util::Object*
sk::io::FileDescriptorOutputStream::
clone() const
{
  return new sk::io::FileDescriptorOutputStream(*this);
}

const sk::util::Class
sk::io::FileDescriptorOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::FileDescriptorOutputStream");
}

void
sk::io::FileDescriptorOutputStream::
close()
{
  _descriptor.close();
}

int
sk::io::FileDescriptorOutputStream::
write(const char* buffer, int offset, int length)
{
  return _descriptor.write(buffer, offset, length);
}

void
sk::io::FileDescriptorOutputStream::
inheritable(bool state)
{
  _descriptor.inheritable(state);
}

const sk::io::FileDescriptor&
sk::io::FileDescriptorOutputStream::
getFileDescriptor() const
{
  return _descriptor;
}
