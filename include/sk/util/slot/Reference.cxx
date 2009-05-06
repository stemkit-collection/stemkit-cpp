/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_SLOT_REFERENCE_CXX_
#define _SK_UTIL_SLOT_REFERENCE_CXX_

#include <sk/util/slot/Reference.hxx>
#include <sk/util/UnsupportedOperationException.h>

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
Reference(T& object)
  : _object(object)
{
}

template<typename T, typename Mixin>
sk::util::slot::Reference<T, Mixin>::
~Reference()
{
}

template<typename T, typename Mixin>
bool
sk::util::slot::Reference<T, Mixin>::
isOwner() const
{
  return false;
}

template<typename T, typename Mixin>
T&
sk::util::slot::Reference<T, Mixin>::
get() const
{
  return _object;
}

template<typename T, typename Mixin>
T*
sk::util::slot::Reference<T, Mixin>::
deprive()
{
  throw sk::util::UnsupportedOperationException("sk::util::slot::Reference#deprive()");
}

template<typename T, typename Mixin>
T*
sk::util::slot::Reference<T, Mixin>::
replace(T* object)
{
  throw sk::util::UnsupportedOperationException("sk::util::slot::Reference#replace()");
}

template<typename T, typename Mixin>
const sk::util::String
sk::util::slot::Reference<T, Mixin>::
inspect() const
{
  return "&";
}

#endif /* _SK_UTIL_SLOT_REFERENCE_CXX_ */
