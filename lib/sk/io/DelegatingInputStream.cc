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

int 
sk::io::DelegatingInputStream::
read(char* buffer, int offset, int length)
{
  return _stream.read(buffer, offset, length);
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

long long
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

void 
sk::io::DelegatingInputStream::
inheritable(bool state)
{
  _stream.inheritable(state);
}
