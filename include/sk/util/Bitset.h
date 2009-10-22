/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_BITSET_H_
#define _SK_UTIL_BITSET_H_

#include <sk/util/Object.h>

namespace sk {
  namespace util {
    class Bitset 
      : public virtual sk::util::Object
    {
      public:
        Bitset();
        Bitset(uint32_t min, uint32_t max);
        virtual ~Bitset();

        inline bool isOn(uint32_t index) const;
        inline bool isOff(uint32_t index) const;

        uint32_t getMin() const;
        uint32_t getMax() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
    
      private:
        Bitset(const Bitset& other);
        Bitset& operator = (const Bitset& other);

        uint32_t* _depot;
        uint32_t _min;
        uint32_t _max;

    };
  }
}

inline bool
sk::util::Bitset::
isOn(uint32_t index) const
{
  return (index < _min || index >= _max) ? false : _depot[index >> 5] & (1 << (index & 0x1f));
}

inline bool
sk::util::Bitset::
isOff(uint32_t index) const
{
  return !isOn(index);
}

#endif /* _SK_UTIL_BITSET_H_ */
