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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Class.h>
#include <sk/util/inspect.h>

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
Reference(T& object)
  : Slot<T, Mixin>(object)
{
}

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
~Reference()
{
}

template<typename T, typename Mixin>
const sk::util::Class
sk::util::slot::Reference<T, Mixin>::
getClass() const
{
  return sk::util::Class("sk::util::slot::Reference");
}

template<typename T, typename Mixin>
bool
sk::util::slot::Reference<T, Mixin>::
isOwner() const
{
  return false;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Reference<T, Mixin>::
deprive()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Mixin>
T*
sk::util::slot::Reference<T, Mixin>::
replace(T* /*object*/)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::slot::Reference<T, Mixin>::
inspect() const
{
  return "&" + sk::util::inspect(*sk::util::Slot<T, Mixin>::_object);
}

#endif /* _SK_UTIL_SLOT_REFERENCE_CXX_ */
