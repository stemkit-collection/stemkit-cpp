/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/ByteArrayOutputStream.h>
#include <sk/io/IOException.h>

sk::io::ByteArrayOutputStream::
ByteArrayOutputStream(std::vector<char>& buffer)
  : _buffer(buffer), _closed(false)
{
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
  if(length<=0) {
    return 0;
  }
  if(_closed == true) {
    throw sk::io::IOException("Closed stream");
  }
  _buffer.insert(_buffer.end(), buffer+offset, buffer+offset+length);
  return length;
}

int 
sk::io::ByteArrayOutputStream::
write(const std::vector<char>& data, int offset)
{
  return AbstractOutputStream::write(data, offset);
}

int 
sk::io::ByteArrayOutputStream::
write(const std::vector<char>& data)
{
  return AbstractOutputStream::write(data);
}

int 
sk::io::ByteArrayOutputStream::
write(char byte)
{
  return AbstractOutputStream::write(byte);
}

void
sk::io::ByteArrayOutputStream::
close()
{
  _closed = true;
}
