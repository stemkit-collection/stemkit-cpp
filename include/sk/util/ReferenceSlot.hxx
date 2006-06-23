/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_REFERENCESLOT_HXX_
#define _SK_UTIL_REFERENCESLOT_HXX_

#include <sk/util/Slot.h>

namespace sk {
  namespace util {
    template<class T>
    class ReferenceSlot
      : public virtual sk::util::Slot<T>
    {
      public:
        ReferenceSlot(T& object);
        virtual ~ReferenceSlot();
        
        // sk::util::Slot re-implementation.
        T& get() const;
        T* deprive();
        
        // sk::util::Object re-implementation.
        const sk::util::String inspect() const;
        
      private:
        ReferenceSlot(const ReferenceSlot<T>& other);
        ReferenceSlot<T>& operator = (const ReferenceSlot<T>& other);

        T& _object;
    };
  }
}

#endif /* _SK_UTIL_REFERENCESLOT_HXX_ */
