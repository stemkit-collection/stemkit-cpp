/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
~FileDescriptorOutputStream()
{
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
