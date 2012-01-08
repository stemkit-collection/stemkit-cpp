/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

sk::util::Object*
sk::io::AbstractInputStream::
clone() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool
sk::io::AbstractInputStream::
markSupported() const
{
  return false;
}

void
sk::io::AbstractInputStream::
mark(int /*readlimit*/)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::io::AbstractInputStream::
reset()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint64_t
sk::io::AbstractInputStream::
available() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

/*
 * Most ineffective implementation. It is to be refined in derrived classes.
*/
int
sk::io::AbstractInputStream::
skip(int number)
{
  int counter;
  for(counter=0; counter<number ;counter++) {
    try {
      read();
    }
    catch(const sk::io::EOFException& exception) {
      break;
    }
  }
  return counter;
}

char
sk::io::AbstractInputStream::
read()
{
  char c;
  filterReadEvents(read(&c, 0, 1));

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
  buffer.resize(filterReadEvents(read(&buffer.front(), 0, number)));

  return buffer;
}

int
sk::io::AbstractInputStream::
filterReadEvents(int n)
{
  if(n==0) {
    throw EOFException();
  }
  if(n<0) {
    throw IOException("read() failed");
  }
  return n;
}
