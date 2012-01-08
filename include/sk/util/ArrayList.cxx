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
#include <sk/util/OpenEndedLists.hxx>

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
  OpenEndedLists<T, Policy, type_t>::addFirst(super_t::_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
addFirst(T& object)
{
  OpenEndedLists<T, Policy, type_t>::addFirst(super_t::_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
addFirst(T* object)
{
  OpenEndedLists<T, Policy, type_t>::addFirst(super_t::_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
removeFirst()
{
  OpenEndedLists<T, Policy, type_t>::removeFirst(super_t::_container);
}

template<typename T, typename Policy>
T*
sk::util::ArrayList<T, Policy>::
cutoffFirst()
{
  return OpenEndedLists<T, Policy, type_t>::cutoffFirst(super_t::_container);
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
