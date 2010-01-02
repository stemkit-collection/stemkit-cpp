/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_REFERENCE_CXX_
#define _SK_UTIL_SLOT_REFERENCE_CXX_

#include <sk/util/slot/Reference.hxx>
#include <sk/util/Slot.cxx>

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
Reference(T& object)
  : Slot<T, Mixin>(object)
{
}

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
Reference(const T& object)
  : Slot<T, Mixin>(object)
{
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::slot::Reference<T, Mixin>::
inspect() const
{
  T* object = sk::util::Slot<T, Mixin>::_object;
  return "&" + (object == 0 ? sk::util::inspect(object) : sk::util::inspect(*object));
}

#endif /* _SK_UTIL_SLOT_REFERENCE_CXX_ */
