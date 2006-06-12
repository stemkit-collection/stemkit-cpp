/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_
#define _SK_UTIL_HOLDER_

#include <sk/util/ReferenceSlot.h>
#include <sk/util/PointerSlot.h>
#include <sk/util/IllegalStateException.h>

namespace sk {
  namespace util {
    template<typename T>
    class Holder
    {
      public:
        Holder();
        explicit Holder(T* object);
        explicit Holder(T& object);
        virtual ~Holder();

        bool contains(const T& object) const;
        bool isEmpty() const;
        T& get() const;

        void set(T* object);
        void set(T& object);

        bool remove();
        void clear();

        T* release();
        
      private:
        Holder(const Holder<T>& other);
        Holder<T>& operator = (const Holder<T>& other);
        Holder<T>& set(const Holder<T>& other);

        Slot<T>* _slot;
    };
  }
}

template<class T>
sk::util::Holder<T>::
Holder()
  : _slot(0)
{
}

template<class T>
sk::util::Holder<T>::
Holder(T& object)
  : _slot(0)
{
  _slot = new ReferenceSlot<T>(object);
}

template<class T>
sk::util::Holder<T>::
Holder(T* object)
  : _slot(0)
{
  _slot = new PointerSlot<T>(object);
}

template<class T>
sk::util::Holder<T>::
~Holder()
{
  delete _slot;
}

template<class T>
T&
sk::util::Holder<T>::
get() const
{
  if(_slot == 0) {
    throw IllegalStateException("get()");
  }
  return _slot->get();
}

template<class T>
bool
sk::util::Holder<T>::
isEmpty() const
{
  return _slot==0 ? true : false;
}

template<class T>
bool
sk::util::Holder<T>::
contains(const T& object) const
{
  if(_slot == 0) {
    return false;
  }
  return &_slot->get() == &object ? true : false;
}

#endif /* _SK_UTIL_HOLDER_ */
