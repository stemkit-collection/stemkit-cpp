/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedOutputStream.h>

sk::io::BufferedOutputStream::
BufferedOutputStream(sk::io::OutputStream& stream)
  : DelegatingOutputStream(stream), _size(1024)
{
}

sk::io::BufferedOutputStream::
BufferedOutputStream(sk::io::OutputStream& stream, int size)
  : DelegatingOutputStream(stream), _size(std::max(0, size))
{
}

sk::io::BufferedOutputStream::
~BufferedOutputStream()
{
}

const sk::util::Class
sk::io::BufferedOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::BufferedOutputStream");
}
