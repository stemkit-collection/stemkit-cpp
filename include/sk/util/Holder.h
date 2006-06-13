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
#include <sk/util/MissingResourceException.h>

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

        Holder<T>& set(T* object);
        Holder<T>& set(T& object);

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
  set(object);
}

template<class T>
sk::util::Holder<T>::
Holder(T* object)
  : _slot(0)
{
  set(object);
}

template<class T>
sk::util::Holder<T>::
~Holder()
{
  remove();
}

template<class T>
sk::util::Holder<T>&
sk::util::Holder<T>::
set(T& object)
{
  remove();
  _slot = new ReferenceSlot<T>(object);
  return *this;
}

template<class T>
sk::util::Holder<T>&
sk::util::Holder<T>::
set(T* object)
{
  remove();
  if(object != 0) {
    _slot = new PointerSlot<T>(object);
  }
  return *this;
}

template<class T>
T&
sk::util::Holder<T>::
get() const
{
  if(_slot == 0) {
    throw MissingResourceException("sk::util::Holder#get()");
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

template<class T>
bool
sk::util::Holder<T>::
remove()
{
  if(_slot == 0) {
    return false;
  }
  delete _slot;
  _slot = 0;

  return true;
}

template<class T>
void
sk::util::Holder<T>::
clear()
{
  remove();
}

template<class T>
T*
sk::util::Holder<T>::
release()
{
  get();

  T* object = _slot->deprive();
  remove();
  set(*object);

  return object;
}

#endif /* _SK_UTIL_HOLDER_ */
