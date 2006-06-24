/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

int 
sk::io::BufferedOutputStream::
write(const char* buffer, int offset, int size)
{
  if(offset < 0) {
    offset = 0;
  }
  if(size < 0) {
    size = 0;
  }
  _buffer.insert(_buffer.end(), buffer+offset, buffer+offset+size);

  if(_buffer.size() > _size) {
    DelegatingOutputStream::write(&_buffer.front(), 0, _size);
    _buffer.erase(_buffer.begin(), _buffer.begin() + _size);
  }
  return size;
}

void 
sk::io::BufferedOutputStream::
flush()
{
  if(_buffer.size() > 0) {
    DelegatingOutputStream::write(&_buffer.front(), 0, _buffer.size());
    _buffer.clear();
  }
}

void 
sk::io::BufferedOutputStream::
close()
{
  flush();
  DelegatingOutputStream::close();
}
