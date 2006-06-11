/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_REFERENCESLOT_
#define _SK_UTIL_REFERENCESLOT_

#include <sk/util/Slot.h>
#include <sk/util/IllegalStateException.h>

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
        
      private:
        ReferenceSlot(const ReferenceSlot<T>& other);
        ReferenceSlot& operator = (const ReferenceSlot<T>& other);

        T& _object;
    };
  }
}

template<class T>
sk::util::ReferenceSlot<T>::
ReferenceSlot(T& object)
  : _object(object)
{
}

template<class T>
sk::util::ReferenceSlot<T>::
~ReferenceSlot()
{
}

template<class T>
T&
sk::util::ReferenceSlot<T>::
get() const
{
  return _object;
}

template<class T>
T*
sk::util::ReferenceSlot<T>::
deprive()
{
  throw sk::util::IllegalStateException("deprive()");
}

#endif /* _SK_UTIL_REFERENCESLOT_ */
