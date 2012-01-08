/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/CountingOutputStream.h>

sk::io::CountingOutputStream::
CountingOutputStream(sk::io::OutputStream& stream)
  : DelegatingOutputStream(stream), _byteCount(0)
{
}

sk::io::CountingOutputStream::
CountingOutputStream(sk::io::OutputStream* stream)
  : DelegatingOutputStream(stream), _byteCount(0)
{
}

sk::io::CountingOutputStream::
~CountingOutputStream()
{
}

const sk::util::Class
sk::io::CountingOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::CountingOutputStream");
}

uint64_t
sk::io::CountingOutputStream::
getByteCount() const
{
  return _byteCount;
}

int
sk::io::CountingOutputStream::
write(const char* buffer, int offset, int size)
{
  int n = DelegatingOutputStream::write(buffer, offset, size);
  if(n > 0) {
      _byteCount += n;
  }
  return n;
}
