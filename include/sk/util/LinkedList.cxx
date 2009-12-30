/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_LINKEDLIST_CXX_
#define _SK_UTIL_LINKEDLIST_CXX_

#include <sk/util/Class.h>
#include <sk/util/LinkedList.hxx>
#include <sk/util/StandardContainer.cxx>
#include <deque>

template<typename T, typename Policy>
sk::util::LinkedList<T, Policy>::
LinkedList()
{
}

template<typename T, typename Policy>
sk::util::LinkedList<T, Policy>::
~LinkedList()
{
}

template<typename T, typename Policy>
const sk::util::Class
sk::util::LinkedList<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::LinkedList");
}

template<typename T, typename Policy>
void 
sk::util::LinkedList<T, Policy>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  super_t::_container.sort(typename super_t::AssessingBinaryFunctor(assessor));
}

template<typename T, typename Policy>
void 
sk::util::LinkedList<T, Policy>::
shuffle()
{
  typedef typename type::list<T, Policy>::item_t item_t;
  typedef std::deque<item_t, std::allocator<item_t> > deque_t;

  deque_t pot(super_t::_container.begin(), super_t::_container.end());
  std::random_shuffle(pot.begin(), pot.end());

  std::copy(pot.begin(), pot.end(), super_t::_container.begin());
}

#endif /* _SK_UTIL_LINKEDLIST_CXX_ */
