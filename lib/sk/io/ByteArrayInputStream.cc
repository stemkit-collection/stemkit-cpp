/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/ByteArrayInputStream.h>
#include <sk/util/NullPointerException.h>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <sk/io/ClosedChannelException.h>
#include <algorithm>

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const char* buffer, int size)
  : _depot(buffer), _depotSize(std::max(0, size))
{
  if(_depot == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  init();
}

sk::io::ByteArrayInputStream::
ByteArrayInputStream(const std::vector<char>& data)
  : _vectorHolder(data), _depotSize(data.size()), _depot(_depotSize==0 ? 0 : &data.front())
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
  _depotOffset = 0;

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

uint64_t
sk::io::ByteArrayInputStream::
available() const
{
  return _depotSize - _depotOffset;
}

int
sk::io::ByteArrayInputStream::
read(char* buffer, int offset, int length)
{
  if(_closed == true) {
    throw sk::io::ClosedChannelException();
  }
  if(buffer == 0 || length <= 0) {
    return 0;
  }
  if(offset < 0) {
    offset = 0;
  }
  if(_vectorHolder.isEmpty() == false) {
    _depotSize = _vectorHolder.get().size();
    _depot = _depotSize==0 ? 0 : &_vectorHolder.get().front();
  }
  int remaining = filterReadEvents(available());

  int number = std::min(std::max(0, length), remaining);
  const char* start = _depot;

  std::copy(_depot + _depotOffset, _depot + _depotOffset + number, buffer + offset);
  _depotOffset += number;
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
  _depotOffset += distance;

  return distance;
}

void
sk::io::ByteArrayInputStream::
mark(int readlimit)
{
  _mark = _depotOffset;
  _markDistance = readlimit;
}

void
sk::io::ByteArrayInputStream::
reset()
{
  if((_depotOffset - _mark) > _markDistance) {
    initMark();
  }
  _depotOffset = _mark;
}

void
sk::io::ByteArrayInputStream::
inheritable(bool /*state*/)
{
}

int
sk::io::ByteArrayInputStream::
getByteCount() const
{
  return _depotOffset;
}
