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
#include <limits>
#include <algorithm>
#include <functional>

static const sk::util::String __className("sk::util::Bitset");

sk::util::Bitset::
Bitset()
  : _max(0), _min(0)
{
  setBounds(32, 0);
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

namespace {
  struct Inspector {
    Inspector(std::ostream& stream)
      : _stream(stream) {}

    void operator()(uint32_t value) const {
      for(int index=32; index; --index, value >>= 1) {
        _stream <<  (value & 1);
      }
    }
    std::ostream& _stream;
  };
}

const sk::util::String
sk::util::Bitset::
inspect() const
{
  std::stringstream stream;

  stream << _min << '<';
  std::for_each(_container.begin(), _container.end(), Inspector(stream));
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
  std::fill(_container.begin(), _container.end(), 0);
}

namespace {
  struct Flipper {
    void operator()(uint32_t& value) const {
      value ^= std::numeric_limits<uint32_t>::max();
    }
  };
}

void 
sk::util::Bitset::
flipAll() 
{
  std::for_each(_container.begin(), _container.end(), Flipper());
}

void
sk::util::Bitset::
setAll()
{
  std::fill(_container.begin(), _container.end(), std::numeric_limits<uint32_t>::max());
}

void 
sk::util::Bitset::
compact() 
{
  container::iterator first = std::find_if(_container.begin(), _container.end(), std::bind2nd(std::not_equal_to<uint32_t>(), 0));
  if(first == _container.end()) {
    setBounds(32, 0);
    return;
  }
  container::reverse_iterator last = std::find_if(_container.rbegin(), _container.rend(), std::bind2nd(std::not_equal_to<uint32_t>(), 0));
  setBounds(_min + ((first - _container.begin()) << 5), _max - 1 - ((last - _container.rbegin()) << 5));
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
  setBounds(bound, _max - 1);
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
  uint32_t lower = sk_util_Bitset_block(lowerBound);
  uint32_t upper = std::max(lower, (sk_util_Bitset_block(upperBound) + 1));

  if(lower == upper) {
    _container.clear();
    _depot = &_container.front();

    _min = 0;
    _max = 0;

    return;
  }

  uint32_t min = sk_util_Bitset_block(_min);
  uint32_t max = sk_util_Bitset_block(_max);

  int lower_delta = min - lower;
  int upper_delta = upper - max;

  int old_size = max - min;
  int new_size = old_size + lower_delta + upper_delta;

  if(new_size > old_size) {
    _container.resize(new_size);
    _depot = &_container.front();
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
    _container.resize(new_size);
    _depot = &_container.front();
  }
  _min = lower << 5;
  _max = upper << 5;
}

int 
sk::util::Bitset::
capacity() const 
{
  return _container.size();
}
