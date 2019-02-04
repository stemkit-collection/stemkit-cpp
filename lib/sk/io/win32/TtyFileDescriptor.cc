/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/UnsupportedOperationException.h>

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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::io::TtyFileDescriptor::
setLines(int /*lines*/)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::io::TtyFileDescriptor::
setColumns(int /*columns*/)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
