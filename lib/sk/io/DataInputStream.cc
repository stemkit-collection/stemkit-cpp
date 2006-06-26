/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/DataInputStream.h>
#include <sk/io/EOFException.h>
#include <sstream>

sk::io::DataInputStream::
DataInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream)
{
}

sk::io::DataInputStream::
~DataInputStream()
{
}

const sk::util::Class
sk::io::DataInputStream::
getClass() const
{
  return sk::util::Class("sk::io::DataInputStream");
}

#include <iostream>
#include <iomanip>

namespace {
  template<class T>
  T readBytesNumber(sk::io::DataInput& stream, int length) {
    T value = 0;
    for(int counter=0; counter<length ;counter++) {
      value |= (int(stream.readChar()) & 0xff) << (8 * counter);
    }
    return value;
  }
}

int 
sk::io::DataInputStream::
readInt()
{
  return readBytesNumber<int>(*this, 4);
}

long long 
sk::io::DataInputStream::
readLong()
{
  return readBytesNumber<long long>(*this, 8);
}

short 
sk::io::DataInputStream::
readShort()
{
  return readBytesNumber<short>(*this, 2);
}

char 
sk::io::DataInputStream::
readChar()
{
  char c;
  readFully(&c, 1);

  return c;
}

double 
sk::io::DataInputStream::
readDouble()
{
  throw sk::util::UnsupportedOperationException("readDouble()");
}

float 
sk::io::DataInputStream::
readFloat()
{
  throw sk::util::UnsupportedOperationException("readFloat()");
}

int 
sk::io::DataInputStream::
skipBytes(int number)
{
  return getInputStream().skip(number);
}

const sk::util::String 
sk::io::DataInputStream::
readLine()
{
  std::stringstream stream;
  try {
    while(true) {
      char c = readChar();
      stream << c;

      if(c=='\n') {
        break;
      }
    }
  }
  catch(const sk::io::EOFException& exception) {
    if(stream.str().empty()) {
      throw;
    }
  }
  return stream.str();
}

std::vector<char>& 
sk::io::DataInputStream::
readFully(std::vector<char>& buffer, int number)
{
  buffer.resize(number<0 ? 0 : number, 0);
  readFully(&buffer.front(), number);

  return buffer;
}

std::vector<char> 
sk::io::DataInputStream::
readFully(int number)
{
  std::vector<char> buffer;
  return readFully(buffer, number);
}

void 
sk::io::DataInputStream::
readFully(char* buffer, int length)
{
  sk::io::InputStream& stream = getInputStream();
  int offset = 0;

  while(offset < length) {
    int n = stream.read(buffer, offset, length-offset);
    if(n == 0) {
      throw sk::io::EOFException();
    }
    if(n < 0) {
      throw sk::io::IOException("sk::io::DataInputStream::readFully()");
    }
    offset += n;
  }
}
