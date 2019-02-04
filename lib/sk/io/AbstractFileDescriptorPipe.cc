/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/AbstractFileDescriptorPipe.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

sk::io::AbstractFileDescriptorPipe::
AbstractFileDescriptorPipe()
{
}

sk::io::AbstractFileDescriptorPipe::
~AbstractFileDescriptorPipe()
{
}

const sk::util::Class
sk::io::AbstractFileDescriptorPipe::
getClass() const
{
  return sk::util::Class("sk::io::AbstractFileDescriptorPipe");
}

void
sk::io::AbstractFileDescriptorPipe::
close()
{
  closeInput();
  closeOutput();
}

void 
sk::io::AbstractFileDescriptorPipe::
closeInput()
{
  _inputStreamHolder.getMutable().close();
}

void 
sk::io::AbstractFileDescriptorPipe::
closeOutput()
{
  _outputStreamHolder.getMutable().close();
}

sk::io::FileDescriptorInputStream& 
sk::io::AbstractFileDescriptorPipe::
inputStream() const
{
  return _inputStreamHolder.getMutable();
}

sk::io::FileDescriptorOutputStream& 
sk::io::AbstractFileDescriptorPipe::
outputStream() const
{
  return _outputStreamHolder.getMutable();
}

void 
sk::io::AbstractFileDescriptorPipe::
setInputFileDescriptor(int fd)
{
  _inputStreamHolder.set(new FileDescriptorInputStream(fd));
}

void 
sk::io::AbstractFileDescriptorPipe::
setOutputFileDescriptor(int fd)
{
  _outputStreamHolder.set(new FileDescriptorOutputStream(fd));
}

void 
sk::io::AbstractFileDescriptorPipe::
setInputFileDescriptor(const sk::io::FileDescriptor& descriptor)
{
  _inputStreamHolder.set(new FileDescriptorInputStream(descriptor));
}

void 
sk::io::AbstractFileDescriptorPipe::
setOutputFileDescriptor(const sk::io::FileDescriptor& descriptor)
{
  _outputStreamHolder.set(new FileDescriptorOutputStream(descriptor));
}
