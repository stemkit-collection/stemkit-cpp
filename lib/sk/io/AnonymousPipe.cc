/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/SystemException.h>

#include <sk/io/AnonymousPipe.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

#include <unistd.h>

sk::io::AnonymousPipe::
AnonymousPipe()
{
  int fds[2];
  
  if(::pipe(fds) < 0) {
    throw sk::util::SystemException("pipe()");
  }

  _inputStreamHolder.set(new sk::io::FileDescriptorInputStream(fds[0]));
  _outputStreamHolder.set(new sk::io::FileDescriptorOutputStream(fds[1]));
}

sk::io::AnonymousPipe::
~AnonymousPipe()
{
}

const sk::util::Class
sk::io::AnonymousPipe::
getClass() const
{
  return sk::util::Class("sk::io::AnonymousPipe");
}

void 
sk::io::AnonymousPipe::
close()
{
  closeInput();
  closeOutput();
}

void 
sk::io::AnonymousPipe::
closeInput()
{
  _inputStreamHolder.get().close();
}

void 
sk::io::AnonymousPipe::
closeOutput()
{
  _outputStreamHolder.get().close();
}

sk::io::InputStream& 
sk::io::AnonymousPipe::
inputStream() const
{
  return _inputStreamHolder.get();
}

sk::io::OutputStream& 
sk::io::AnonymousPipe::
outputStream() const
{
  return _outputStreamHolder.get();
}
