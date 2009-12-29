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

#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <sk/io/ClosedChannelException.h>

sk::io::ByteArrayOutputStream::
ByteArrayOutputStream(std::vector<char>& buffer)
  : _vectorHolder(buffer), _depot(0), _depotSize(0), _depotOffset(0), 
    _closed(false)
{
}

sk::io::ByteArrayOutputStream::
ByteArrayOutputStream(char* buffer, uint64_t size)
  : _depot(buffer), _depotSize(size), _depotOffset(0), 
    _closed(false)
{
  if(_depot == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
}

sk::io::ByteArrayOutputStream::
~ByteArrayOutputStream()
{
}

const sk::util::Class
sk::io::ByteArrayOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::ByteArrayOutputStream");
}

int 
sk::io::ByteArrayOutputStream::
write(const char* buffer, int offset, int length)
{
  if((buffer == 0) || (length <= 0)) {
    return 0;
  }
  if(_closed == true) {
    throw sk::io::ClosedChannelException();
  }
  if(offset < 0) {
    offset = 0;
  }
  int guaranteed_length = length;
  if(_depotSize > 0) {
    guaranteed_length = std::min(uint64_t(length), _depotSize - _depotOffset);
  }
  if(_vectorHolder.isEmpty() == false) {
      _vectorHolder.get().resize(_depotOffset + guaranteed_length);
      _depot = &_vectorHolder.get().front();
  }
  std::copy(buffer + offset, buffer + offset + guaranteed_length, _depot + _depotOffset);
  _depotOffset += guaranteed_length;

  if(length > guaranteed_length) {
    throw sk::io::EOFException();
  }
  return guaranteed_length;
}

void
sk::io::ByteArrayOutputStream::
close()
{
  _closed = true;
}

void
sk::io::ByteArrayOutputStream::
inheritable(bool /*state*/)
{
}

uint64_t
sk::io::ByteArrayOutputStream::
getByteCount() const
{
    return _depotOffset;
}
