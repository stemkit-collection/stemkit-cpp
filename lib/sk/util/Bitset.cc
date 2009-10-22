/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Bitset.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sstream>
#include <algorithm>

static const sk::util::String __className("sk::util::Bitset");

static const uint32_t SK_BITMAP_BLOCKSIZE = 1024;

sk::util::Bitset::
Bitset()
  : _depot(0), _min(0), _max(0)
{
}

sk::util::Bitset::
Bitset(uint32_t min, uint32_t max)
  : _depot(0), _min(block(min) << 5), _max(std::max(_min, (block(max) + 1) << 5))
{
  int size = std::max(_max - _min, SK_BITMAP_BLOCKSIZE);
  _max = _min + size;

  _depot = new uint32_t[size];
  std::fill(_depot, _depot + size, 0);
}

sk::util::Bitset::
~Bitset()
{
  if(_depot) {
    delete [] _depot;
  }
}

const sk::util::Class
sk::util::Bitset::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::Bitset::
inspect() const
{
  std::stringstream stream;
  stream << _min << '<';

  int size = _max - _min;
  for(int index=0; index < size; ++index) {
    uint32_t value = _depot[index];
    for(int index=32; index; --index, value >>= 1) {
      stream << '0' + (value & 1);
    }
  }
  stream << '>' << _max;

  return stream.str();
}

uint32_t
sk::util::Bitset::
getMin() const
{
  return _min;
}

uint32_t
sk::util::Bitset::
getMax() const
{
  return _max;
}

void
sk::util::Bitset::
clearAll()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::util::Bitset::
flipAll() 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::util::Bitset::
setAll()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void
sk::util::Bitset::
ensure(uint32_t index) 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
