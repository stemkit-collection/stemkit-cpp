/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_RANDOMACCESSCONTAINER_CXX_
#define _SK_UTIL_RANDOMACCESSCONTAINER_CXX_

#include <sk/util/Class.h>
#include <sk/util/RandomAccessContainer.hxx>
#include <sk/util/StandardContainer.cxx>
#include <sk/util/Collections.hxx>
#include <sk/util/Validator.h>

template<typename T, typename Policy, typename Type>
sk::util::RandomAccessContainer<T, Policy, Type>::
RandomAccessContainer()
{
}

template<typename T, typename Policy, typename Type>
sk::util::RandomAccessContainer<T, Policy, Type>::
~RandomAccessContainer()
{
}

template<typename T, typename Policy, typename Type>
const sk::util::Class
sk::util::RandomAccessContainer<T, Policy, Type>::
getClass() const
{
  return sk::util::Class("sk::util::RandomAccessContainer");
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  std::sort(super_t::_container.begin(), super_t::_container.end(), typename super_t::AssessingBinaryFunctor(assessor));
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
shuffle()
{
  std::random_shuffle(super_t::_container.begin(), super_t::_container.end());
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::iterator
sk::util::RandomAccessContainer<T, Policy, Type>::
position(int index, int tailOffset)
{
  sk::util::Validator::ensureIndex(index, super_t::_container.size() + tailOffset);
  return super_t::_container.begin() + index;
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::const_iterator
sk::util::RandomAccessContainer<T, Policy, Type>::
position(int index, int tailOffset) const
{
  sk::util::Validator::ensureIndex(index, super_t::_container.size() + tailOffset);
  return super_t::_container.begin() + index;
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
add(int index, const T& object)
{
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
add(int index, T& object)
{
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
add(int index, T* object)
{
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
const T&
sk::util::RandomAccessContainer<T, Policy, Type>::
get(int index) const
{
  return Policy::getObject(*position(index, 0));
}

template<typename T, typename Policy, typename Type>
T&
sk::util::RandomAccessContainer<T, Policy, Type>::
getMutable(int index) const
{
  return Policy::getMutableObject(*position(index, 0));
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
remove(int index)
{
  remove(position(index, 0));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::RandomAccessContainer<T, Policy, Type>::
cutoff(int index)
{
  return cutoff(position(index, 0));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::RandomAccessContainer<T, Policy, Type>::
release(int index)
{
  return release(position(index, 0));
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
set(int index, const T& object)
{
  Policy::setObject(*position(index, 0) , object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
set(int index, T& object)
{
  Policy::setObject(*position(index, 0) , object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::RandomAccessContainer<T, Policy, Type>::
set(int index, T* object)
{
  Policy::setObject(*position(index, 0) , object);
}

#endif /* _SK_UTIL_RANDOMACCESSCONTAINER_CXX_ */
