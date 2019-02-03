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
#include <sk/util/Class.h>

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
Slot(T* object)
  : _object(object) 
{
  if(_object == 0) {
    throw sk::util::NullPointerException(SK_METHOD);
  }
}

template<typename T, typename Mixin>
sk::util::Slot<T, Mixin>::
Slot(T& object)
  : _object(&object) 
{
}

#endif /* _SK_UTIL_SLOT_CXX_ */
