/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/IllegalStateException.h>

#include <sk/io/TtyFileDescriptor.h>

#include <unistd.h>

sk::io::TtyFileDescriptor::
TtyFileDescriptor(int fd)
  : sk::io::FileDescriptor(fd)
{
  ensureTty();
}

sk::io::TtyFileDescriptor::
TtyFileDescriptor(const sk::io::FileDescriptor& descriptor)
  : sk::io::FileDescriptor(descriptor)
{
  ensureTty();
}

sk::io::TtyFileDescriptor::
~TtyFileDescriptor()
{
}

const sk::util::Class
sk::io::TtyFileDescriptor::
getClass() const
{
  return sk::util::Class("sk::io::TtyFileDescriptor");
}

void 
sk::io::TtyFileDescriptor::
ensureTty()
{
  int fd = getFileNumber();
  if(!isatty(fd)) {
    throw sk::util::IllegalStateException("Not a tty (" + sk::util::Integer::toString(fd) + ")");
  }
}

void
sk::io::TtyFileDescriptor::
setLines(int lines)
{
  // TODO: Provide actual implementation, ignoring the call for now.
  // throw sk::util::UnsupportedOperationException("setLines()");
}

void 
sk::io::TtyFileDescriptor::
setColumns(int columns)
{
  // TODO: Provide actual implementation, ignoring the call for now.
  // throw sk::util::UnsupportedOperationException("setColumns()");
}
