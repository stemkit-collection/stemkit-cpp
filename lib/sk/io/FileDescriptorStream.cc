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

#include <sk/io/FileDescriptorStream.h>
#include <sk/util/upcast.cxx>

static const char* __className("sk::io::FileDescriptorStream");

sk::io::FileDescriptorStream::
FileDescriptorStream(const sk::io::Stream& stream)
  : _descriptor(sk::util::upcast<sk::io::FileDescriptorProvider>(stream).getFileDescriptor())
{
}

sk::io::FileDescriptorStream::
FileDescriptorStream(const sk::io::FileDescriptorStream& other)
  : _descriptor(other._descriptor)
{
}

sk::io::FileDescriptorStream::
~FileDescriptorStream()
{
}

const sk::util::Class
sk::io::FileDescriptorStream::
getClass() const
{
  return sk::util::Class(__className);
}

sk::io::FileDescriptorStream*
sk::io::FileDescriptorStream::
clone() const
{
  return new sk::io::FileDescriptorStream(*this);
}

void 
sk::io::FileDescriptorStream::
close()
{
  _descriptor.close();
}

const sk::io::FileDescriptor&
sk::io::FileDescriptorStream::
getFileDescriptor() const
{
  return _descriptor;
}
