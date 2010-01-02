/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_CXX_
#define _SK_UTIL_HOLDER_CXX_

#include <sk/util/Holder.hxx>
#include <sk/util/slot/Reference.cxx>
#include <sk/util/slot/Pointer.cxx>
#include <sk/util/inspect.h>

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder()
  : _storage(0)
{
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Storing& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Direct& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Copying& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Cloning& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Aliasing& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Sharing& other)
  : _storage(0)
{
  Policy::acceptSlot(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(T& object)
  : _storage(0)
{
  set(object);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const T& object)
  : _storage(0)
{
  set(object);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(T* object)
  : _storage(0)
{
  set(object);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
~Holder()
{
  remove();
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Storing& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Direct& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Copying& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Cloning& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Aliasing& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Sharing& other)
{
  Policy::acceptSlot(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
const typename Policy::slot_t& 
sk::util::Holder<T, Policy>::
getSlot() const
{
  return Policy::getSlot(_storage);
}

template<typename T, typename Policy>
void
sk::util::Holder<T, Policy>::
set(const T& object)
{
  Policy::setObject(_storage, object);
}

template<typename T, typename Policy>
void
sk::util::Holder<T, Policy>::
set(T& object)
{
  Policy::setObject(_storage, object);
}

template<typename T, typename Policy>
void
sk::util::Holder<T, Policy>::
set(T* object)
{
  Policy::setObject(_storage, object);
}

template<typename T, typename Policy>
const T&
sk::util::Holder<T, Policy>::
get() const
{
  return Policy::getObject(_storage);
}

template<typename T, typename Policy>
T&
sk::util::Holder<T, Policy>::
getMutable()
{
  return Policy::getMutableObject(_storage);
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isOwner() const
{
  return Policy::isObjectOwner(_storage);
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isEmpty() const
{
  return Policy::hasSlot(_storage) == false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isMutable() const
{
  return Policy::hasMutableObject(_storage);
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
contains(const T& object) const
{
  if(Policy::hasSlot(_storage) == false) {
    return false;
  }
  return &Policy::getObject(_storage) == &object ? true : false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
remove()
{
  if(Policy::hasSlot(_storage) == false) {
    return false;
  }
  Policy::clearSlot(_storage);

  return true;
}

template<typename T, typename Policy>
void
sk::util::Holder<T, Policy>::
clear()
{
  remove();
}

template<typename T, typename Policy>
T*
sk::util::Holder<T, Policy>::
release()
{
  T* object = Policy::depriveObject(_storage);
  Policy::setObject(_storage, *object);

  return object;
}

template<typename T, typename Policy>
T*
sk::util::Holder<T, Policy>::
deprive() 
{
  return Policy::depriveObject(_storage);
}

template<typename T, typename Policy>
const sk::util::String
sk::util::Holder<T, Policy>::
inspect() const
{
  if(isEmpty() == true) {
    return "()";
  }
  return "(" + Policy::inspectSlot(_storage) + ")";
}

#endif /* _SK_UTIL_HOLDER_CXX_ */
