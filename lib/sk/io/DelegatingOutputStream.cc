/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/DelegatingOutputStream.h>

sk::io::DelegatingOutputStream::
DelegatingOutputStream(sk::io::OutputStream& stream)
  : _stream(stream)
{
}

sk::io::DelegatingOutputStream::
~DelegatingOutputStream()
{
}

const sk::util::Class
sk::io::DelegatingOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::DelegatingOutputStream");
}

sk::io::OutputStream&
sk::io::DelegatingOutputStream::
getOutputStream() const 
{
  return _stream;
}

void 
sk::io::DelegatingOutputStream::
close()
{
  _stream.close();
}

void 
sk::io::DelegatingOutputStream::
flush()
{
  _stream.flush();
}

int 
sk::io::DelegatingOutputStream::
write(const char* buffer, int offset, int length)
{
  return _stream.write(buffer, offset, length);
}

int 
sk::io::DelegatingOutputStream::
write(const std::vector<char>& data, int offset)
{
  return _stream.write(data, offset);
}

int 
sk::io::DelegatingOutputStream::
write(const std::vector<char>& data)
{
  return _stream.write(data);
}

int 
sk::io::DelegatingOutputStream::
write(char byte)
{
  return _stream.write(byte);
}
