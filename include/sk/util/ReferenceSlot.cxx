/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_REFERENCESLOT_CXX_
#define _SK_UTIL_REFERENCESLOT_CXX_

#include <sk/util/ReferenceSlot.hxx>
#include <sk/util/UnsupportedOperationException.h>

template<typename T, typename Mixin>
sk::util::ReferenceSlot<T, Mixin>::
ReferenceSlot(T& object)
  : _object(object)
{
}

template<typename T, typename Mixin>
sk::util::ReferenceSlot<T, Mixin>::
~ReferenceSlot()
{
}

template<typename T, typename Mixin>
bool
sk::util::ReferenceSlot<T, Mixin>::
isOwner() const
{
  return false;
}

template<typename T, typename Mixin>
T&
sk::util::ReferenceSlot<T, Mixin>::
get() const
{
  return _object;
}

template<typename T, typename Mixin>
T*
sk::util::ReferenceSlot<T, Mixin>::
deprive()
{
  throw sk::util::UnsupportedOperationException("sk::util::ReferenceSlot#deprive()");
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::ReferenceSlot<T, Mixin>::
inspect() const
{
  return '&';
}

#endif /* _SK_UTIL_REFERENCESLOT_CXX_ */
