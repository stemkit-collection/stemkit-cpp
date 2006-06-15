/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/ByteArrayInputStream.h>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <algorithm>

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const char* buffer, int size)
  : _bufferHolder(new std::vector<char>(buffer, buffer + (size<0 ? 0 : size)))
{
  reset();
}

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const std::vector<char>& buffer)
  : _bufferHolder(buffer)
{
  reset();
}

sk::io::ByteArrayInputStream::
~ByteArrayInputStream()
{
}

void
sk::io::ByteArrayInputStream::
reset()
{
  _closed = false;
  _cursor = 0;
}

const sk::util::Class
sk::io::ByteArrayInputStream::
getClass() const
{
  return sk::util::Class("sk::io::ByteArrayInputStream");
}

void
sk::io::ByteArrayInputStream::
close()
{
}

int 
sk::io::ByteArrayInputStream::
available() const
{
  return _bufferHolder.get().size() - _cursor;
}

int
sk::io::ByteArrayInputStream::
read(char* buffer, int offset, int length)
{
  if(_closed == true) {
    throw IOException("Closed stream");
  }
  int remaining = available();
  if(remaining == 0) {
    throw EOFException();
  }
  int number = std::min(std::max(0, length), remaining);
  std::vector<char>::const_iterator start = _bufferHolder.get().begin();

  std::copy(start + _cursor, start + _cursor + number, buffer+offset);
  _cursor += number;
  return number;
}

char
sk::io::ByteArrayInputStream::
read()
{
  return AbstractInputStream::read();
}

std::vector<char> 
sk::io::ByteArrayInputStream::
read(int number)
{
  return AbstractInputStream::read(number);
}

std::vector<char>& 
sk::io::ByteArrayInputStream::
read(std::vector<char>& buffer, int number)
{
  return AbstractInputStream::read(buffer, number);
}
