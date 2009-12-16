/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_HXX_
#define _SK_UTIL_SLOT_HXX_

#include <sk/util/Object.h>
#include <sk/util/Class.h>
#include <sk/util/MissingResourceException.h>
#include <sk/util/slot/mixin/None.h>

namespace sk {
  namespace util {
    template<typename T, typename Mixin = slot::mixin::None>
    class Slot
      : public virtual sk::util::Object,
        public Mixin
    {
      public:
        Slot(T& object);
        Slot(T* object);

        inline T& get() const;

        virtual bool isOwner() const = 0;
        virtual T* deprive() = 0;
        virtual T* replace(T* object) = 0;

      private:
        Slot(const Slot<T, Mixin>& other);
        Slot<T, Mixin>& operator = (const Slot<T, Mixin>& other);

      protected:
        T* _object;
    };
  }
}

template<typename T, typename Mixin>
inline T&
sk::util::Slot<T, Mixin>::
get() const
{
  if(_object == 0) {
    throw sk::util::MissingResourceException(SK_METHOD);
  }
  return *_object;
}

#endif /* _SK_UTIL_SLOT_HXX_ */
