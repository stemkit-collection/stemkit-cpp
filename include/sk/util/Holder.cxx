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
  Policy::makeCopy(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Copying& other)
  : _storage(0)
{
  Policy::makeCopy(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Cloning& other)
  : _storage(0)
{
  Policy::makeCopy(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Aliasing& other)
  : _storage(0)
{
  Policy::makeCopy(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const Sharing& other)
  : _storage(0)
{
  Policy::makeCopy(_storage, other._storage);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(Sharing& other)
  : _storage(0)
{
  Policy::makeCopy(_storage, other._storage);
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
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Copying& other)
{
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Cloning& other)
{
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Aliasing& other)
{
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(const Sharing& other)
{
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
operator=(Sharing& other)
{
  Policy::makeCopy(_storage, other._storage);
  return *this;
}

template<typename T, typename Policy>
const typename Policy::slot_type& 
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
  return Policy::getSlot(_storage).get();
}

template<typename T, typename Policy>
T&
sk::util::Holder<T, Policy>::
getMutable()
{
  return Policy::getSlot(_storage).getMutable();
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isOwner() const
{
  return Policy::getSlot(_storage).isOwner();
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
contains(const T& object) const
{
  if(Policy::hasSlot(_storage) == false) {
    return false;
  }
  return &Policy::getSlot(_storage).get() == &object ? true : false;
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
  T* object = Policy::getSlot(_storage).deprive();
  remove();
  set(*object);

  return object;
}

template<typename T, typename Policy>
T*
sk::util::Holder<T, Policy>::
deprive() 
{
  return Policy::getSlot(_storage).deprive();
}

template<typename T, typename Policy>
const sk::util::String
sk::util::Holder<T, Policy>::
inspect() const
{
  if(isEmpty() == true) {
    return "()";
  }
  return "(" + Policy::getSlot(_storage).inspect() + ")";
}

#endif /* _SK_UTIL_HOLDER_CXX_ */
