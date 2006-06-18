/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/FileDescriptorInputStream.h>

sk::io::FileDescriptorInputStream::
FileDescriptorInputStream(int fd)
  : _descriptor(fd)
{
}

sk::io::FileDescriptorInputStream::
FileDescriptorInputStream(const sk::io::FileDescriptor& descriptor)
  : _descriptor(descriptor)
{
}

sk::io::FileDescriptorInputStream::
~FileDescriptorInputStream()
{
}

const sk::util::Class
sk::io::FileDescriptorInputStream::
getClass() const
{
  return sk::util::Class("sk::io::FileDescriptorInputStream");
}

void 
sk::io::FileDescriptorInputStream::
close()
{
  _descriptor.close();
}

int 
sk::io::FileDescriptorInputStream::
read(char* buffer, int offset, int length)
{
  return _descriptor.read(buffer, offset, length);
}
