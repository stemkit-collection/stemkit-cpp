/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/CountingInputStream.h>

sk::io::CountingInputStream::
CountingInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream), _byteCount(0)
{
}

sk::io::CountingInputStream::
CountingInputStream(sk::io::InputStream* stream)
  : DelegatingInputStream(stream), _byteCount(0)
{
}

sk::io::CountingInputStream::
~CountingInputStream()
{
}

const sk::util::Class
sk::io::CountingInputStream::
getClass() const
{
  return sk::util::Class("sk::io::CountingInputStream");
}

uint64_t
sk::io::CountingInputStream::
getByteCount() const
{
  return _byteCount;
}

int
sk::io::CountingInputStream::
read(char* buffer, int offset, int size)
{
  int n = DelegatingInputStream::read(buffer, offset, size);
  if(n > 0) {
    _byteCount += n;
  }
  return n;
}
