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

#include <sk/io/DelegatingOutputStream.h>

sk::io::DelegatingOutputStream::
DelegatingOutputStream(sk::io::OutputStream& stream)
  : _streamHolder(stream)
{
}

sk::io::DelegatingOutputStream::
DelegatingOutputStream(sk::io::OutputStream* stream)
  : _streamHolder(stream)
{
}

sk::io::DelegatingOutputStream::
~DelegatingOutputStream()
{
}

const sk::util::Class
sk::io::DelegatingOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::DelegatingOutputStream");
}

sk::io::OutputStream&
sk::io::DelegatingOutputStream::
getOutputStream() const
{
  return _streamHolder.getMutable();
}

void
sk::io::DelegatingOutputStream::
close()
{
  _streamHolder.getMutable().close();
}

void
sk::io::DelegatingOutputStream::
flush()
{
  _streamHolder.getMutable().flush();
}

int
sk::io::DelegatingOutputStream::
write(const char* buffer, int offset, int length)
{
  return _streamHolder.getMutable().write(buffer, offset, length);
}

void
sk::io::DelegatingOutputStream::
inheritable(bool state)
{
  _streamHolder.getMutable().inheritable(state);
}
