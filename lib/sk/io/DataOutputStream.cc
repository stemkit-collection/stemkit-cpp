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

namespace {
  template<class T>
  void writeByteNumber(sk::io::DataOutput& stream, T& value, int length) {
    const char* data = reinterpret_cast<const char*>(&value);
    for(int index=0; index < length; ++index) {
      stream.writeChar(*(data + index));
    }
  }
}

void
sk::io::DataOutputStream::
writeInt(uint32_t value)
{
  writeByteNumber(*this, value, 4);
}

void
sk::io::DataOutputStream::
writeLong(uint64_t value)
{
  writeByteNumber(*this, value, 8);
}

void
sk::io::DataOutputStream::
writeShort(uint16_t value)
{
  writeByteNumber(*this, value, 2);
}

void
sk::io::DataOutputStream::
writeDouble(double /*value*/)
{
  throw sk::util::UnsupportedOperationException("writeDouble()");
}

void
sk::io::DataOutputStream::
writeFloat(float /*value*/)
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
  int length = value.size();
  if(length > 0) {
    writeFully(&value.front(), length);
  }
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
  for(int offset = 0; offset < length; offset += stream.write(buffer, offset, length - offset));
}
