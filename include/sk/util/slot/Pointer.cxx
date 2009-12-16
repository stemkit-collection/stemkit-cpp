/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POINTER_CXX_
#define _SK_UTIL_SLOT_POINTER_CXX_

#include <sk/util/slot/Pointer.hxx>
#include <sk/util/Slot.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NullPointerException.h>
#include <sk/util/inspect.h>

template<typename T, typename Mixin>
sk::util::slot::Pointer<T, Mixin>::
Pointer(T* object)
  : Slot<T, Mixin>(object)
{
}

template<typename T, typename Mixin>
sk::util::slot::Pointer<T, Mixin>::
~Pointer()
{
  delete sk::util::Slot<T, Mixin>::_object;
}

template<typename T, typename Mixin>
const sk::util::Class
sk::util::slot::Pointer<T, Mixin>::
getClass() const
{
  return sk::util::Class("sk::util::slot::Pointer");
}

template<typename T, typename Mixin>
bool
sk::util::slot::Pointer<T, Mixin>::
isOwner() const
{
  return true;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Pointer<T, Mixin>::
deprive()
{
  if(sk::util::Slot<T, Mixin>::_object == 0) {
    throw MissingResourceException(SK_METHOD);
  }
  T* object = sk::util::Slot<T, Mixin>::_object;
  sk::util::Slot<T, Mixin>::_object = 0;

  return object;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Pointer<T, Mixin>::
replace(T* object)
{
  if(object == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
  if(sk::util::Slot<T, Mixin>::_object == 0) {
    throw MissingResourceException(SK_METHOD);
  }
  T* original = sk::util::Slot<T, Mixin>::_object;
  sk::util::Slot<T, Mixin>::_object = object;

  return original;
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::slot::Pointer<T, Mixin>::
inspect() const
{
  T* object = sk::util::Slot<T, Mixin>::_object;
  return "*" + (object == 0 ? sk::util::inspect(object) : sk::util::inspect(*object));
}

#endif /* _SK_UTIL_SLOT_POINTER_CXX_ */
