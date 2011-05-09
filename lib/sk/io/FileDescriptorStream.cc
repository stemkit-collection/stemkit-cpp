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
#include <sk/util/Holder.cxx>

#include <sk/io/FileDescriptorStream.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>
#include <sk/util/upcast.cxx>

static const sk::util::String __className("sk::io::FileDescriptorStream");

sk::io::FileDescriptorStream::
FileDescriptorStream(const int fd)
  : _descriptor(fd)
{
}

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

sk::util::Object*
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
  _inputStreamHolder.clear();
  _outputStreamHolder.clear();
}

const sk::io::FileDescriptor&
sk::io::FileDescriptorStream::
getFileDescriptor() const
{
  return _descriptor;
}

void
sk::io::FileDescriptorStream::
inheritable(bool state)
{
  _descriptor.inheritable(state);
}

sk::io::InputStream&
sk::io::FileDescriptorStream::
inputStream() const
{
  if(_inputStreamHolder.isEmpty() == true) {
    _inputStreamHolder.set(new FileDescriptorInputStream(_descriptor));
  }
  return _inputStreamHolder.getMutable();
}

sk::io::OutputStream&
sk::io::FileDescriptorStream::
outputStream() const
{
  if(_outputStreamHolder.isEmpty() == true) {
    _outputStreamHolder.set(new FileDescriptorOutputStream(_descriptor));
  }
  return _outputStreamHolder.getMutable();
}
