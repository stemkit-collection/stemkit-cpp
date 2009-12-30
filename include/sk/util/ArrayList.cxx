/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_ARRAYLIST_CXX_
#define _SK_UTIL_ARRAYLIST_CXX_

#include <sk/util/Class.h>
#include <sk/util/ArrayList.hxx>
#include <sk/util/StandardContainer.cxx>

template<typename T, typename Policy>
sk::util::ArrayList<T, Policy>::
ArrayList()
{
}

template<typename T, typename Policy>
sk::util::ArrayList<T, Policy>::
~ArrayList()
{
}

template<typename T, typename Policy>
const sk::util::Class
sk::util::ArrayList<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::ArrayList");
}

template<typename T, typename Policy>
void 
sk::util::ArrayList<T, Policy>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  std::sort(super_t::_container.begin(), super_t::_container.end(), typename super_t::AssessingBinaryFunctor(assessor));
}

template<typename T, typename Policy>
void 
sk::util::ArrayList<T, Policy>::
shuffle()
{
  std::random_shuffle(super_t::_container.begin(), super_t::_container.end());
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
