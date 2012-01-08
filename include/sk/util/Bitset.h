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
#include <vector>

namespace sk {
  namespace util {
    class Bitset
      : public virtual sk::util::Object
    {
      public:
        Bitset();
        Bitset(uint32_t lowerBound, uint32_t upperBound);
        Bitset(uint32_t upperBound);
        virtual ~Bitset();

        inline bool isOn(uint32_t index) const;
        inline bool isOff(uint32_t index) const;
        inline bool clear(uint32_t index);
        inline bool flip(uint32_t index);
        inline bool set(uint32_t index);

        void clearAll();
        void flipAll();
        void setAll();

        uint32_t getMin() const;
        uint32_t getMax() const;

        int capacity() const;

        void setUpperBound(uint32_t upper);
        void setLowerBound(uint32_t upper);
        void setBounds(uint32_t lower, uint32_t upper);
        void ensure(uint32_t index);
        void compact();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;

      private:
        Bitset(const Bitset& other);
        Bitset& operator = (const Bitset& other);

        static inline uint32_t block(uint32_t index);
        static inline uint32_t bit(uint32_t index);

        typedef std::vector<uint32_t> container;
        container _container;
        uint32_t* _depot;
        uint32_t _min;
        uint32_t _max;
    };
  }
}

inline uint32_t
sk::util::Bitset::
block(uint32_t index)
{
  return index >> 5;
}

inline uint32_t
sk::util::Bitset::
bit(uint32_t index)
{
  return 1 << (index & 0x1f);
}

inline bool
sk::util::Bitset::
isOn(uint32_t index) const
{
  return (index < _min || index >= _max) ? false : _depot[block(index - _min)] & bit(index);
}

inline bool
sk::util::Bitset::
isOff(uint32_t index) const
{
  return !isOn(index);
}

inline bool
sk::util::Bitset::
clear(uint32_t index)
{
  if(isOn(index) == true) {
    _depot[block(index - _min)] &= ~bit(index);
    return true;
  }
  return false;
}

inline bool
sk::util::Bitset::
flip(uint32_t index)
{
  ensure(index);
  return !(_depot[block(index - _min)] ^= bit(index));
}

inline bool
sk::util::Bitset::
set(uint32_t index)
{
  if(isOn(index) == false) {
    ensure(index);
    _depot[block(index - _min)] |= bit(index);

    return false;
  }
  return true;
}

#endif /* _SK_UTIL_BITSET_H_ */
