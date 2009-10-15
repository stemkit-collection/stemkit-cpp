/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_POINTER_CXX_
#define _SK_UTIL_SLOT_POINTER_CXX_

#include <sk/util/slot/Pointer.hxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NullPointerException.h>
#include <sk/util/inspect.h>

template<typename T, typename Mixin>
sk::util::slot::Pointer<T, Mixin>::
Pointer(T* object)
  : _object(object)
{
  if(_object == 0) {
    throw NullPointerException("sk::util::slot::Pointer()");
  }
}

template<typename T, typename Mixin>
sk::util::slot::Pointer<T, Mixin>::
~Pointer()
{
  delete _object;
}

template<typename T, typename Mixin>
bool
sk::util::slot::Pointer<T, Mixin>::
isOwner() const
{
  return true;
}

template<typename T, typename Mixin>
T&
sk::util::slot::Pointer<T, Mixin>::
get() const
{
  if(_object == 0) {
    throw MissingResourceException("sk::util::slot::Pointer#get()");
  }
  return *_object;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Pointer<T, Mixin>::
deprive()
{
  if(_object == 0) {
    throw MissingResourceException("sk::util::slot::Pointer#deprive()");
  }
  T* object = _object;
  _object = 0;

  return object;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Pointer<T, Mixin>::
replace(T* object)
{
  T* original = _object;
  _object = object;

  return original;
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::slot::Pointer<T, Mixin>::
inspect() const
{
  return "*" + (_object == 0 ? sk::util::inspect(_object) : sk::util::inspect(*_object));
}

#endif /* _SK_UTIL_SLOT_POINTER_CXX_ */
