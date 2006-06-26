/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/ByteArrayInputStream.h>
#include <sk/util/Holder.cxx>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <sk/io/ClosedChannelException.h>
#include <algorithm>

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const char* buffer, int size)
  : _bufferHolder(new std::vector<char>(buffer, buffer + (size<0 ? 0 : size)))
{
  init();
}

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const std::vector<char>& buffer)
  : _bufferHolder(buffer)
{
  init();
}

sk::io::ByteArrayInputStream::
~ByteArrayInputStream()
{
}

void
sk::io::ByteArrayInputStream::
init()
{
  _closed = false;
  _cursor = 0;

  initMark();
}

void
sk::io::ByteArrayInputStream::
initMark()
{
  _mark = 0;
  _markDistance = 0;
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

off_t
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
    throw sk::io::ClosedChannelException();
  }
  int remaining = available();
  if(remaining == 0) {
    return 0;
  }
  int number = std::min(std::max(0, length), remaining);
  std::vector<char>::const_iterator start = _bufferHolder.get().begin();

  std::copy(start + _cursor, start + _cursor + number, buffer+offset);
  _cursor += number;
  return number;
}

bool
sk::io::ByteArrayInputStream::
markSupported() const
{
  return true;
}

int 
sk::io::ByteArrayInputStream::
skip(int number)
{
  int distance = std::min(number, int(available()));
  _cursor += distance;

  return distance;
}

void
sk::io::ByteArrayInputStream::
mark(int readlimit)
{
  _mark = _cursor;
  _markDistance = readlimit;
}

void 
sk::io::ByteArrayInputStream::
reset()
{
  if((_cursor - _mark) > _markDistance) {
    initMark();
  }
  _cursor = _mark;
}
