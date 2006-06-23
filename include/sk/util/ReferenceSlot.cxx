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

template<class T>
sk::util::ReferenceSlot<T>::
ReferenceSlot(T& object)
  : _object(object)
{
}

template<class T>
sk::util::ReferenceSlot<T>::
~ReferenceSlot()
{
}

template<class T>
T&
sk::util::ReferenceSlot<T>::
get() const
{
  return _object;
}

template<class T>
T*
sk::util::ReferenceSlot<T>::
deprive()
{
  throw sk::util::UnsupportedOperationException("sk::util::ReferenceSlot#deprive()");
}

template<class T>
const sk::util::String
sk::util::ReferenceSlot<T>::
inspect() const
{
  return '&';
}

#endif /* _SK_UTIL_REFERENCESLOT_CXX_ */
