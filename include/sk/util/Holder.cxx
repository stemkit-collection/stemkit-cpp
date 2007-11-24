/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder()
{
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(T& object)
{
  set(object);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(T* object)
{
  set(object);
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>::
Holder(const slot::policy::Storing<T>& other)
  : Policy(other)
{
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
set(T& object)
{
  remove();

  Policy::setObject(object);
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
set(T* object)
{
  remove();
  
  if(object != 0) {
    Policy::setObject(object);
  }
  return *this;
}

template<typename T, typename Policy>
T&
sk::util::Holder<T, Policy>::
get() const
{
  return Policy::getSlot().get();
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isOwner() const
{
  return Policy::getSlot().isOwner();
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isEmpty() const
{
  return Policy::hasSlot() == false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
contains(const T& object) const
{
  if(Policy::hasSlot() == false) {
    return false;
  }
  return &Policy::getSlot().get() == &object ? true : false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
remove()
{
  if(Policy::hasSlot() == false) {
    return false;
  }
  Policy::clearSlot();

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
  T* object = Policy::getSlot().deprive();
  remove();
  set(*object);

  return object;
}

#endif /* _SK_UTIL_HOLDER_CXX_ */
