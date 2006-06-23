/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_POINTERSLOT_CXX_
#define _SK_UTIL_POINTERSLOT_CXX_

#include <sk/util/PointerSlot.hxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NullPointerException.h>

template<class T>
sk::util::PointerSlot<T>::
PointerSlot(T* object)
  : _object(object)
{
  if(_object == 0) {
    throw NullPointerException("sk::util::PointerSlot()");
  }
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
    throw MissingResourceException("sk::util::PointerSlot#get()");
  }
  return *_object;
}

template<class T>
T*
sk::util::PointerSlot<T>::
deprive()
{
  if(_object == 0) {
    throw MissingResourceException("sk::util::PointerSlot#deprive()");
  }
  T* object = _object;
  _object = 0;

  return object;
}

template<class T>
const sk::util::String
sk::util::PointerSlot<T>::
inspect() const
{
  return '*';
}

#endif /* _SK_UTIL_POINTERSLOT_CXX_ */
