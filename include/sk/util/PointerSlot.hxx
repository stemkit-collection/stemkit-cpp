/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_POINTERSLOT_HXX_
#define _SK_UTIL_POINTERSLOT_HXX_

#include <sk/util/Slot.hxx>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    template<class T>
    class PointerSlot
      : public virtual sk::util::Slot<T>
    {
      public:
        PointerSlot(T* object);
        virtual ~PointerSlot();
        
        // sk::util::Slot re-implementation.
        bool isOwner() const;
        T& get() const;
        T* deprive();
        
        // sk::util::Object re-implementation.
        const sk::util::String inspect() const;
        
      private:
        PointerSlot(const PointerSlot<T>& other);
        PointerSlot<T>& operator = (const PointerSlot<T>& other);

        T* _object;
    };
  }
}

#endif /* _SK_UTIL_POINTERSLOT_HXX_ */
