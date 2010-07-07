/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedOutputStream.h>
#include <algorithm>

sk::io::BufferedOutputStream::
BufferedOutputStream(sk::io::OutputStream& stream)
  : DelegatingOutputStream(stream), _size(1024), _amount(0), _buffer(_size, 0), _stream(getOutputStream())
{
}

sk::io::BufferedOutputStream::
BufferedOutputStream(sk::io::OutputStream& stream, int size)
  : DelegatingOutputStream(stream), _size(std::max(1, size)), _amount(0), _buffer(_size, 0), _stream(getOutputStream())
{
}

sk::io::BufferedOutputStream::
~BufferedOutputStream()
{
  flushBuffer();
}

const sk::util::Class
sk::io::BufferedOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::BufferedOutputStream");
}

int 
sk::io::BufferedOutputStream::
write(const char* buffer, int offset, int length)
{
  if(length <= 0) {
    return 0;
  }
  if(buffer == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  if(offset < 0) {
    offset = 0;
  }

  for(int index = 0; index < length; index += collect(buffer + offset + index, length - index));
  return length;
}

int 
sk::io::BufferedOutputStream::
collect(const char* buffer, size_t length)
{
  int amount = _size - _amount;
  if(amount > length) {
    amount = length;
  }
  std::copy(buffer, buffer + amount, &_buffer[_amount]);
  _amount += amount;

  if(_amount == _size) {
    flushBuffer();
  }
  return amount;
}

void
sk::io::BufferedOutputStream::
flushBuffer()
{
  for(int index = 0; index < _amount; index += _stream.write(&_buffer[0], index, _amount - index));
  _amount = 0;
}

void 
sk::io::BufferedOutputStream::
flush()
{
  flushBuffer();
  _stream.flush();
}

void 
sk::io::BufferedOutputStream::
close()
{
  flush();
  _stream.close();
}
