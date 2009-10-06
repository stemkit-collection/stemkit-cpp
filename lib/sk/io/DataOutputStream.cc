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
#include <sk/util/ClassCastException.h>

#include <sk/io/DataOutputStream.h>

sk::io::DataOutputStream::
DataOutputStream(sk::io::OutputStream& stream)
  : DelegatingOutputStream(stream)
{
}

sk::io::DataOutputStream::
~DataOutputStream()
{
}

const sk::util::Class
sk::io::DataOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::DataOutputStream");
}

sk::io::DataOutput&
sk::io::DataOutputStream::
reuseOrMake(sk::io::OutputStream& stream, sk::util::Holder<sk::io::DataOutput>& holder)
{
  sk::io::DataOutput* object = dynamic_cast<sk::io::DataOutput*>(&stream);
  if(object) {
    holder.set(*object);
  }
  else {
    holder.set(new sk::io::DataOutputStream(stream));
  }
  return holder.get();
}

namespace {
  template<class T>
  void writeByteNumber(sk::io::DataOutput& stream, T& value, int length) {
    for(int counter=length; counter ;counter--,value>>=8) {
      stream.writeChar(char(value&0xff));
    }
  }
}

void 
sk::io::DataOutputStream::
writeInt(int value)
{
  writeByteNumber(*this, value, 4);
}

void 
sk::io::DataOutputStream::
writeLong(long long value)
{
  writeByteNumber(*this, value, 8);
}

void 
sk::io::DataOutputStream::
writeShort(short value)
{
  writeByteNumber(*this, value, 2);
}

void 
sk::io::DataOutputStream::
writeDouble(double value)
{
  throw sk::util::UnsupportedOperationException("writeDouble()");
}

void 
sk::io::DataOutputStream::
writeFloat(float value)
{
  throw sk::util::UnsupportedOperationException("writeFloat()");
}

void 
sk::io::DataOutputStream::
writeChar(char value)
{
  writeFully(&value, 1);
}

void 
sk::io::DataOutputStream::
writeChars(const std::string& value)
{
  writeFully(value.c_str(), value.size());
}

void 
sk::io::DataOutputStream::
writeFully(const std::vector<char>& value)
{
  writeFully(&value.front(), value.size());
}

void 
sk::io::DataOutputStream::
writeFully(const char* buffer, int length)
{
  if(length <= 0) {
    return;
  }
  if(buffer == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  sk::io::OutputStream& stream = getOutputStream();
  int offset = 0;

  while(offset < length) {
    offset += stream.write(buffer, offset, length - offset);
  }
}
