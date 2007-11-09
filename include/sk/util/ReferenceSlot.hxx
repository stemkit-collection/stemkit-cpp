/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_REFERENCESLOT_HXX_
#define _SK_UTIL_REFERENCESLOT_HXX_

#include <sk/util/MixableSlot.hxx>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    template<typename T, typename Mixin = DefautlSlotMixin>
    class ReferenceSlot
      : public sk::util::MixableSlot<T, Mixin>
    {
      public:
        ReferenceSlot(T& object);
        virtual ~ReferenceSlot();
        
        // sk::util::Slot re-implementation.
        bool isOwner() const;
        T& get() const;
        T* deprive();
        
        // sk::util::Object re-implementation.
        const sk::util::String inspect() const;
        
      private:
        ReferenceSlot(const ReferenceSlot<T, Mixin>& other);
        ReferenceSlot<T, Mixin>& operator = (const ReferenceSlot<T, Mixin>& other);

        T& _object;
    };
  }
}

#endif /* _SK_UTIL_REFERENCESLOT_HXX_ */
