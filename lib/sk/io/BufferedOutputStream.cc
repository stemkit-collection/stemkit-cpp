/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedOutputStream.h>
#include <sk/io/IOException.h>

#include <algorithm>
#include <iostream>

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
  flushChunks(0);
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

  flushChunks(_size);
  return size;
}

void
sk::io::BufferedOutputStream::
flushChunks(int chunk_size)
{
  int written = 0;
  int buffer_size = _buffer.size();
  
  while(true) {
    int remaining = buffer_size - written;
    int outstanding = (chunk_size == 0 ? remaining : chunk_size);

    if(outstanding == 0 || remaining < outstanding) {
      break;
    }
    int n = DelegatingOutputStream::write(&_buffer.front(), written, outstanding);
    if(n == 0) {
      break;
    }
    written += n;
  }
  if(written != 0) {
    _buffer.erase(_buffer.begin(), _buffer.begin() + written);
  }
}

void 
sk::io::BufferedOutputStream::
flush()
{
  flushChunks(0);

  if(_buffer.empty() == false) {
    throw sk::io::IOException("Buffer flush failed");
  }
}

void 
sk::io::BufferedOutputStream::
close()
{
  flush();
  DelegatingOutputStream::close();
}
