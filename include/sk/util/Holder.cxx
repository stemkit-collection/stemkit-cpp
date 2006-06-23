/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_CXX_
#define _SK_UTIL_HOLDER_CXX_

#include <sk/util/Holder.hxx>
#include <sk/util/ReferenceSlot.cxx>
#include <sk/util/PointerSlot.cxx>
#include <sk/util/MissingResourceException.h>

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

#endif /* _SK_UTIL_HOLDER_CXX_ */
