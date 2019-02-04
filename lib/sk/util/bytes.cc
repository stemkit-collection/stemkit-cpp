/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/bytes.h>
#include <sk/util/inspect.h>
#include <sstream>

sk::util::bytes::
bytes() 
  : std::vector<uint8_t>() 
{
}

sk::util::bytes::
bytes(uint8_t value)
  : std::vector<uint8_t>(1, value) 
{
}

sk::util::bytes::
bytes(const std::vector<uint8_t>& other)
  : std::vector<uint8_t>(other) 
{
}

namespace {
  bool output_with_delimiter(std::ostream& stream, const sk::util::bytes& items, const sk::util::String& delimiter) {
    if(items.empty() == false) {
      sk::util::bytes::const_iterator iterator = items.begin();
      stream << uint32_t(*iterator);
      while(++iterator != items.end()) {
        stream << delimiter << uint32_t(*iterator);
      }
      return true;
    }
    return false;
  }
}

const sk::util::String 
sk::util::bytes::
join(const sk::util::String& delimiter) const
{
  std::stringstream stream;
  output_with_delimiter(stream, *this, delimiter);

  return stream.str();
}

const sk::util::String
sk::util::bytes::
inspect() const
{
  return sk::util::inspect(*this);
}

sk::util::bytes& 
sk::util::bytes::
operator << (uint8_t value) 
{
  push_back(value);
  return *this;
}

const sk::util::bytes 
sk::util::bytes::
operator + (uint8_t value) const 
{
  return sk::util::bytes(*this) << value;
}

const sk::util::bytes 
sk::util::bytes::
operator + (const sk::util::bytes& other) const 
{
  std::vector<uint8_t> result(*this);
  result.insert(result.end(), other.begin(), other.end());
  return result;
}

std::ostream& 
sk::util::operator << (std::ostream& stream, const sk::util::bytes& items) 
{
  stream << "[ ";
  if(output_with_delimiter(stream, items, ", ") == true) {
    stream << " ";
  }
  return stream << "]";
}
