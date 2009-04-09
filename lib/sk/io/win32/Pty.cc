/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

sk::io::Pty::
Pty()
  : _scope(*this)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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

const sk::util::String
sk::io::Pty::
getName() const
{
  return _name;
}

void 
sk::io::Pty::
close()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::io::Pty::
closeTty()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::Tty& 
sk::io::Pty::
getTty()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::io::Tty& 
sk::io::Pty::
getTty() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::FileDescriptorPipe& 
sk::io::Pty::
getMasterSlavePipe()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::io::FileDescriptorPipe& 
sk::io::Pty::
getSlaveMasterPipe()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
