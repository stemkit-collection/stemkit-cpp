/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SLOT_ORDERING_CXX_
#define _SK_UTIL_SLOT_ORDERING_CXX_

#include <sk/util/slot/Ordering.hxx>

template<typename T>
sk::util::slot::Ordering<T>::
Ordering()
  : _checker(*this)
{
}

template<typename T>
sk::util::slot::Ordering<T>::
Ordering(const sk::util::OrderingChecker<T>& checker)
  : _checker(checker)
{
}

template<typename T>
bool 
sk::util::slot::Ordering<T>::
operator()(const sk::util::Slot<T>* first, const sk::util::Slot<T>* second) const
{
  return _checker.isOrdered(first->get(), second->get());
}

template<typename T>
bool 
sk::util::slot::Ordering<T>::
isOrdered(const T& first, const T& second) const
{
  return first < second;
}

#endif /* _SK_UTIL_SLOT_ORDERING_CXX_ */
