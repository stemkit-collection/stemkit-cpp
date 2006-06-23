/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedInputStream.h>

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream), _size(1024)
{
}

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream, int size)
  : DelegatingInputStream(stream), _size(std::max(0, size))
{
}

sk::io::BufferedInputStream::
~BufferedInputStream()
{
}

const sk::util::Class
sk::io::BufferedInputStream::
getClass() const
{
  return sk::util::Class("sk::io::BufferedInputStream");
}
