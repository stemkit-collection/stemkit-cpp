/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/AbstractPipe.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

sk::io::AbstractPipe::
AbstractPipe()
{
}

sk::io::AbstractPipe::
~AbstractPipe()
{
}

const sk::util::Class
sk::io::AbstractPipe::
getClass() const
{
  return sk::util::Class("sk::io::AbstractPipe");
}

void
sk::io::AbstractPipe::
close()
{
  closeInput();
  closeOutput();
}

void 
sk::io::AbstractPipe::
closeInput()
{
  _inputStreamHolder.get().close();
}

void 
sk::io::AbstractPipe::
closeOutput()
{
  _outputStreamHolder.get().close();
}

sk::io::FileDescriptorInputStream& 
sk::io::AbstractPipe::
inputStream() const
{
  return _inputStreamHolder.get();
}

sk::io::FileDescriptorOutputStream& 
sk::io::AbstractPipe::
outputStream() const
{
  return _outputStreamHolder.get();
}

void 
sk::io::AbstractPipe::
setInputFileDescriptor(int fd)
{
  _inputStreamHolder.set(new FileDescriptorInputStream(fd));
}

void 
sk::io::AbstractPipe::
setOutputFileDescriptor(int fd)
{
  _outputStreamHolder.set(new FileDescriptorOutputStream(fd));
}

void 
sk::io::AbstractPipe::
setInputFileDescriptor(const sk::io::FileDescriptor& descriptor)
{
  _inputStreamHolder.set(new FileDescriptorInputStream(descriptor));
}

void 
sk::io::AbstractPipe::
setOutputFileDescriptor(const sk::io::FileDescriptor& descriptor)
{
  _outputStreamHolder.set(new FileDescriptorOutputStream(descriptor));
}
