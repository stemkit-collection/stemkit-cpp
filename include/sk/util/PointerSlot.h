/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_POINTERSLOT_
#define _SK_UTIL_POINTERSLOT_

#include <sk/util/Slot.h>
#include <sk/util/IllegalStateException.h>

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
        T& get() const;
        T* deprive();
        
        // sk::util::Object re-implementation.
        const sk::util::String inspect() const;
        
      private:
        PointerSlot(const PointerSlot& other);
        PointerSlot& operator = (const PointerSlot& other);

        T* _object;
    };
  }
}

template<class T>
sk::util::PointerSlot<T>::
PointerSlot(T* object)
  : _object(object)
{
}

template<class T>
sk::util::PointerSlot<T>::
~PointerSlot()
{
  delete _object;
}

template<class T>
T&
sk::util::PointerSlot<T>::
get() const
{
  if(_object == 0) {
    throw IllegalStateException("get()");
  }
  return *_object;
}

template<class T>
T*
sk::util::PointerSlot<T>::
deprive()
{
  if(_object == 0) {
    throw IllegalStateException("deprive()");
  }
  T* result = _object;
  _object = 0;

  return result;
}

template<class T>
const sk::util::String
sk::util::PointerSlot<T>::
inspect() const
{
  return '*';
}

#endif /* _SK_UTIL_POINTERSLOT_ */
