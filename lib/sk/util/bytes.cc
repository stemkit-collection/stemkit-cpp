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
#include <algorithm>
#include <iterator>

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
  stream << "[";
  if(items.empty() == false) {
    sk::util::bytes::const_iterator iterator = items.begin();
    stream << " " << uint32_t(*iterator);
    while(++iterator != items.end()) {
      stream << ", " << uint32_t(*iterator);
    }
  }
  return stream << " ]";
}
