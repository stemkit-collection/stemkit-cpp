/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/Pty.h>
#include "PtyImpl.h"

sk::io::Pty::
Pty()
{
}

sk::io::Pty::
~Pty()
{
}

const sk::util::Class
sk::io::Pty::
getClass() const
{
  return sk::util::Class("sk::io::Pty");
}

void 
sk::io::Pty::
close()
{
  closeInput();
  closeOutput();
}


void 
sk::io::Pty::
closeInput()
{
  throw sk::util::UnsupportedOperationException("closeInput()");
}

void 
sk::io::Pty::
closeOutput()
{
  throw sk::util::UnsupportedOperationException("closeOutput()");
}

sk::io::FileDescriptorInputStream& 
sk::io::Pty::
inputStream() const
{
  throw sk::util::UnsupportedOperationException("inputStream()");
}

sk::io::FileDescriptorOutputStream& 
sk::io::Pty::
outputStream() const
{
  throw sk::util::UnsupportedOperationException("outputStream()");
}

sk::io::Tty& 
sk::io::Pty::
getTty()
{
  return _implHolder.get().getTty();
}

const sk::io::Tty& 
sk::io::Pty::
getTty() const
{
  return _implHolder.get().getTty();
}
