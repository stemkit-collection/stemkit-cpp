/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/io/DelegatingInputStream.h>

sk::io::DelegatingInputStream::
DelegatingInputStream(sk::io::InputStream& stream)
  : _streamHolder(stream)
{
}

sk::io::DelegatingInputStream::
DelegatingInputStream(sk::io::InputStream* stream)
  : _streamHolder(stream)
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
  return _streamHolder.get();
}

int 
sk::io::DelegatingInputStream::
read(char* buffer, int offset, int length)
{
  return _streamHolder.get().read(buffer, offset, length);
}

void 
sk::io::DelegatingInputStream::
close()
{
  _streamHolder.get().close();
}

int 
sk::io::DelegatingInputStream::
skip(int number)
{
  return _streamHolder.get().skip(number);
}

long long
sk::io::DelegatingInputStream::
available() const
{
  return _streamHolder.get().available();
}

bool 
sk::io::DelegatingInputStream::
markSupported() const
{
  return _streamHolder.get().markSupported();
}

void 
sk::io::DelegatingInputStream::
mark(int readlimit)
{
  _streamHolder.get().mark(readlimit);
}

void 
sk::io::DelegatingInputStream::
reset()
{
  _streamHolder.get().reset();
}

void 
sk::io::DelegatingInputStream::
inheritable(bool state)
{
  _streamHolder.get().inheritable(state);
}
