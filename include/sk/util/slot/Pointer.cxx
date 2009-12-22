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

#endif /* _SK_UTIL_SLOT_POINTER_CXX_ */
