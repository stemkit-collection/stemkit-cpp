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

template<typename T, typename Mixin>
sk::util::PointerSlot<T, Mixin>::
PointerSlot(T* object)
  : _object(object)
{
  if(_object == 0) {
    throw NullPointerException("sk::util::PointerSlot()");
  }
}

template<typename T, typename Mixin>
sk::util::PointerSlot<T, Mixin>::
~PointerSlot()
{
  delete _object;
}

template<typename T, typename Mixin>
bool
sk::util::PointerSlot<T, Mixin>::
isOwner() const
{
  return true;
}

template<typename T, typename Mixin>
T&
sk::util::PointerSlot<T, Mixin>::
get() const
{
  if(_object == 0) {
    throw MissingResourceException("sk::util::PointerSlot#get()");
  }
  return *_object;
}

template<typename T, typename Mixin>
T*
sk::util::PointerSlot<T, Mixin>::
deprive()
{
  if(_object == 0) {
    throw MissingResourceException("sk::util::PointerSlot#deprive()");
  }
  T* object = _object;
  _object = 0;

  return object;
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::PointerSlot<T, Mixin>::
inspect() const
{
  return '*';
}

#endif /* _SK_UTIL_POINTERSLOT_CXX_ */
