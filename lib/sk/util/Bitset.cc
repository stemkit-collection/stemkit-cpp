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
#include <sk/util/InsufficientMemoryException.h>

#include <sstream>
#include <algorithm>

static const sk::util::String __className("sk::util::Bitset");

sk::util::Bitset::
Bitset()
  : _max(0), _min(0)
{
}

sk::util::Bitset::
Bitset(uint32_t upperBound)
  : _max(0), _min(0)
{
  setBounds(0, upperBound);
}

sk::util::Bitset::
Bitset(uint32_t lowerBound, uint32_t upperBound)
  : _max(0), _min(0)
{
  setBounds(lowerBound, upperBound);
}

sk::util::Bitset::
~Bitset()
{
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
  if(index < _min) {
    setLowerBound(index);
  }
  else if(index >= _max) {
    setUpperBound(index);
  }
}

void 
sk::util::Bitset::
setLowerBound(uint32_t bound)
{
  setBounds(bound, _max);
}

void 
sk::util::Bitset::
setUpperBound(uint32_t bound)
{
  setBounds(_min, bound);
}

void 
sk::util::Bitset::
setBounds(uint32_t lowerBound, uint32_t upperBound)
{
  uint32_t lower = block(lowerBound);
  uint32_t upper = std::max(lower, (block(upperBound) + 1));

  uint32_t min = block(_min);
  uint32_t max = block(_max);

  int lower_delta = min - lower;
  int upper_delta = upper - max;

  int old_size = max - min;
  int new_size = old_size + lower_delta + upper_delta;

  if(new_size > old_size) {
    _depotContainer.resize(new_size);
    _depot = &_depotContainer.front();
  }

  if(lower_delta > 0) {
    std::copy(_depot, _depot + new_size, _depot + lower_delta);
    std::fill(_depot, _depot + lower_delta, 0);
  }

  if(lower_delta < 0) {
    std::copy(_depot + (-lower_delta), _depot + (-lower_delta) + new_size, _depot);
  }

  if(new_size > old_size) {
    std::fill(_depot + old_size, _depot + new_size, 0);
  }
  else {
    _depotContainer.resize(new_size);
    _depot = &_depotContainer.front();
  }
  _min = lower;
  _max = upper;
}
