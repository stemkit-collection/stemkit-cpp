/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/AbstractPipe.h>

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
  throw sk::util::UnsupportedOperationException("closeInput()");
}

void 
sk::io::AbstractPipe::
closeOutput()
{
  throw sk::util::UnsupportedOperationException("closeOutput()");
}

sk::io::FileDescriptorInputStream& 
sk::io::AbstractPipe::
inputStream() const
{
  throw sk::util::UnsupportedOperationException("inputStream()");
}

sk::io::FileDescriptorOutputStream& 
sk::io::AbstractPipe::
outputStream() const
{
  throw sk::util::UnsupportedOperationException("outputStream()");
}
