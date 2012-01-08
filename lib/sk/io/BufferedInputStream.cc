/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedInputStream.h>
#include <sk/io/EOFException.h>

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream), _size(1024), _amount(0), _offset(0), _buffer(_size, 0), _stream(getInputStream())
{
}

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream, int size)
  : DelegatingInputStream(stream), _size(std::max(1, size)), _amount(0), _offset(0), _buffer(_size, 0), _stream(getInputStream())
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

int
sk::io::BufferedInputStream::
read(char* buffer, int offset, int size)
{
  if(size <= 0) {
    return 0;
  }
  if(buffer == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  if(offset < 0) {
    offset = 0;
  }

  int available = _amount - _offset;
  if(available == 0) {
    _amount = filterReadEvents(_stream.read(&_buffer[0], 0, _size));
    _offset = 0;
    available = _amount;
  }
  int amount = std::min(available, size);

  std::copy(_buffer.begin() + _offset, _buffer.begin() + _offset + amount, buffer + offset);
  _offset += amount;

  return amount;
}
