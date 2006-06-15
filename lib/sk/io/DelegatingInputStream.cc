/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/DelegatingInputStream.h>

sk::io::DelegatingInputStream::
DelegatingInputStream(sk::io::InputStream& stream)
  : _stream(stream)
{
}

sk::io::DelegatingInputStream::
~DelegatingInputStream()
{
}

const sk::util::Class
sk::io::DelegatingInputStream::
getClass() const
{
  return sk::util::Class("sk::io::DelegatingInputStream");
}

sk::io::InputStream& 
sk::io::DelegatingInputStream::
getInputStream() const
{
  return _stream;
}

char 
sk::io::DelegatingInputStream::
read()
{
  return _stream.read();
}

int 
sk::io::DelegatingInputStream::
read(char* buffer, int offset, int length)
{
  return _stream.read(buffer, offset, length);
}

std::vector<char> 
sk::io::DelegatingInputStream::
read(int number)
{
  return _stream.read(number);
}

std::vector<char>& 
sk::io::DelegatingInputStream::
read(std::vector<char>& buffer, int number)
{
  return _stream.read(buffer, number);
}

void 
sk::io::DelegatingInputStream::
close()
{
  _stream.close();
}

int 
sk::io::DelegatingInputStream::
skip(int number)
{
  return _stream.skip(number);
}

int 
sk::io::DelegatingInputStream::
available() const
{
  return _stream.available();
}

bool 
sk::io::DelegatingInputStream::
markSupported() const
{
  return _stream.markSupported();
}

void 
sk::io::DelegatingInputStream::
mark(int readlimit)
{
  _stream.mark(readlimit);
}

void 
sk::io::DelegatingInputStream::
reset()
{
  _stream.reset();
}
