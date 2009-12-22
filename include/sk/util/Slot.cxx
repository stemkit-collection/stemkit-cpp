/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_SLOT_CXX_
#define _SK_UTIL_SLOT_CXX_

#include <sk/util/Slot.hxx>
#include <sk/util/NullPointerException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/inspect.h>

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
Slot(const T& object)
  : _object(const_cast<T*>(&object))
{
  setMutable(false);
  setOwner(false);
}

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
Slot(T& object)
  : _object(&object)
{
  setMutable(true);
  setOwner(false);
}

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
Slot(T* object)
  : _object(object)
{
  if(_object == 0) {
    throw sk::util::NullPointerException("sk::util::Slot<>::Slot()");
  }
  setMutable(true);
  setOwner(true);
}

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
~Slot()
{
}

template<typename T, typename Mixin>
void
sk::util::Slot<T, Mixin>::
setMutable(bool state) 
{
  _traits.set(0, state);
}

template<typename T, typename Mixin>
void
sk::util::Slot<T, Mixin>::
setOwner(bool state) 
{
  _traits.set(1, state);
}

template<typename T, typename Mixin>
T*
sk::util::Slot<T, Mixin>::
deprive()
{
  if(isOwner() == false) {
    throw sk::util::UnsupportedOperationException("deprive()");
  }
  if(sk::util::Slot<T, Mixin>::_object == 0) {
    throw MissingResourceException("deprive()");
  }
  T* object = sk::util::Slot<T, Mixin>::_object;
  sk::util::Slot<T, Mixin>::_object = 0;

  return object;
}

template<typename T, typename Mixin>
T*
sk::util::Slot<T, Mixin>::
replace(T* object)
{
  if(isOwner() == false) {
    throw sk::util::UnsupportedOperationException("replace()");
  }
  if(object == 0) {
    throw sk::util::NullPointerException("replace()");
  }
  if(sk::util::Slot<T, Mixin>::_object == 0) {
    throw MissingResourceException("replace()");
  }
  T* original = sk::util::Slot<T, Mixin>::_object;
  sk::util::Slot<T, Mixin>::_object = object;

  return original;
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::Slot<T, Mixin>::
inspect() const
{
  T* object = sk::util::Slot<T, Mixin>::_object;
  return (isOwner() == true ? "*" : "&") + (object == 0 ? sk::util::inspect(object) : sk::util::inspect(*object));
}

#endif /* _SK_UTIL_SLOT_CXX_ */
