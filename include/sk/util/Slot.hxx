/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_HXX_
#define _SK_UTIL_SLOT_HXX_

#include <sk/util/MissingResourceException.h>
#include <sk/util/ImmutableObjectException.h>
#include <sk/util/slot/mixin/None.h>
#include <bitset>

namespace sk {
  namespace util {
    template<typename T, typename Mixin = slot::mixin::None>
    class Slot
      : public Mixin
    {
      public:
        Slot(const Slot<T, Mixin>& other);
        virtual ~Slot();

        inline bool isEmpty() const;
        inline bool isMutable() const;
        inline bool isOwner() const;

        inline const T& get() const;
        inline T& getMutable() const;

        T* deprive();
        T* replace(T* object);

        virtual const sk::util::String inspect() const = 0;

      protected:
        Slot(const T& object);
        Slot(T& object);
        Slot(T* object);

        T* _object;

      private:
        Slot<T, Mixin>& operator = (const Slot<T, Mixin>& other);

        void setOwner(bool state);
        void setMutable(bool state);

        std::bitset<8> _traits;
    };
  }
}

template<typename T, typename Mixin>
inline bool
sk::util::Slot<T, Mixin>::
isEmpty() const
{
  return _object == 0;
}

template<typename T, typename Mixin>
inline bool
sk::util::Slot<T, Mixin>::
isMutable() const
{
  return _traits.test(0);
}

template<typename T, typename Mixin>
inline bool
sk::util::Slot<T, Mixin>::
isOwner() const
{
  return _traits.test(1);
}

template<typename T, typename Mixin>
inline const T&
sk::util::Slot<T, Mixin>::
get() const
{
  if(_object == 0) {
    throw sk::util::MissingResourceException("get()");
  }
  return *_object;
}

template<typename T, typename Mixin>
inline T&
sk::util::Slot<T, Mixin>::
getMutable() const
{
  if(_object == 0) {
    throw sk::util::MissingResourceException("getMutable()");
  }
  if(isMutable() == false) {
    throw sk::util::ImmutableObjectException("getMutable()");
  }
  return *_object;
}

#endif /* _SK_UTIL_SLOT_HXX_ */
