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

namespace {
  template<class T>
  T readBytesNumber(sk::io::DataInput& stream) {
    T value = 0;
    int length = sizeof(value);

    char* data = reinterpret_cast<char*>(&value);
    for(int index=0; index<length; ++index) {
      *(data + index) = stream.readChar();
    }
    return value;
  }
}

uint32_t
sk::io::DataInputStream::
readInt()
{
  return readBytesNumber<uint32_t>(*this);
}

uint64_t 
sk::io::DataInputStream::
readLong()
{
  return readBytesNumber<uint64_t>(*this);
}

uint16_t 
sk::io::DataInputStream::
readShort()
{
  return readBytesNumber<uint16_t>(*this);
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
  std::ostringstream stream;
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
  if(length <= 0) {
    return;
  }
  if(buffer == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  sk::io::InputStream& stream = getInputStream();
  int offset = 0;

  while(offset < length) {
    offset += filterReadEvents(stream.read(buffer, offset, length-offset));
  }
}
