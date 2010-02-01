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
#include <sk/util/RandomAccessContainer.cxx>
#include <sk/util/Collections.hxx>

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
addFirst(const T& object)
{
  super_t::_container.push_front(Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void 
sk::util::ArrayList<T, Policy>::
addFirst(T& object)
{
  super_t::_container.push_front(Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void 
sk::util::ArrayList<T, Policy>::
addFirst(T* object)
{
  super_t::_container.push_front(Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void 
sk::util::ArrayList<T, Policy>::
removeFirst()
{
  sk::util::Validator::ensureNotEmpty(super_t::_container.size());
  Policy::clearSlot(super_t::_container.front());
  super_t::_container.pop_front();
}

template<typename T, typename Policy>
T*
sk::util::ArrayList<T, Policy>::
cutoffFirst()
{
  sk::util::Validator::ensureNotEmpty(super_t::_container.size());
  T* object = Policy::depriveObject(super_t::_container.front());
  super_t::_container.pop_front();

  return object;
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
