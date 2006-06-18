/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/AbstractInputStream.h>
#include <sk/io/IOException.h>
#include <sk/io/EOFException.h>
#include <sk/util/UnsupportedOperationException.h>

const sk::util::Class
sk::io::AbstractInputStream::
getClass() const
{
  return sk::util::Class("sk::io::AbstractInputStream");
}

bool
sk::io::AbstractInputStream::
markSupported() const
{
  return false;
}

void
sk::io::AbstractInputStream::
mark(int readlimit) 
{
  throw sk::util::UnsupportedOperationException("sk::io::AbstractInputStream::mark()");
}

void 
sk::io::AbstractInputStream::
reset()
{
  throw sk::util::UnsupportedOperationException("sk::io::AbstractInputStream::reset()");
}

int
sk::io::AbstractInputStream::
available() const
{
  throw sk::util::UnsupportedOperationException("sk::io::AbstractInputStream::available()");
}

int
sk::io::AbstractInputStream::
skip(int number)
{
  throw sk::util::UnsupportedOperationException("sk::io::AbstractInputStream::skip()");
}

char
sk::io::AbstractInputStream::
read()
{
  char c;
  int n = read(&c, 0, 1);

  if(n==0) {
    throw EOFException();
  }
  if(n<0) {
    throw IOException("sk::io::AbstractInputStream::read()");
  }
  return int(c) & 0xff;
}

std::vector<char> 
sk::io::AbstractInputStream::
read(int number)
{
  std::vector<char> buffer;
  return read(buffer, number);
}

std::vector<char>& 
sk::io::AbstractInputStream::
read(std::vector<char>& buffer, int number)
{
  if(number<=0) {
    buffer.resize(0);
    return buffer;
  }
  buffer.resize(number, 0);

  int n = read(&buffer.front(), 0, number);
  if(n==0) {
    throw EOFException();
  }
  if(n<0) {
    throw IOException("sk::io::AbstractInputStream::read(vector, number)");
  }
  buffer.resize(n);
  return buffer;
}
