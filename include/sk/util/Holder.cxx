/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_HOLDER_CXX_
#define _SK_UTIL_HOLDER_CXX_

#include <sk/util/Holder.hxx>
#include <sk/util/ReferenceSlot.cxx>
#include <sk/util/PointerSlot.cxx>
#include <sk/util/MissingResourceException.h>

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
  _slot = new ReferenceSlot<T, SlotActions>(object);
  
  return *this;
}

template<typename T, typename Policy>
sk::util::Holder<T, Policy>&
sk::util::Holder<T, Policy>::
set(T* object)
{
  remove();
  if(object != 0) {
    _slot = 0; // new PointerSlot<T, SlotActions>(object);
  }
  return *this;
}

template<typename T, typename Policy>
T&
sk::util::Holder<T, Policy>::
get() const
{
  if(_slot == 0) {
    throw MissingResourceException("sk::util::Holder#get()");
  }
  return _slot->get();
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isOwner() const
{
  if(_slot == 0) {
    throw MissingResourceException("sk::util::Holder#isOwner()");
  }
  return _slot->isOwner();
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
isEmpty() const
{
  return _slot==0 ? true : false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
contains(const T& object) const
{
  if(_slot == 0) {
    return false;
  }
  return &_slot->get() == &object ? true : false;
}

template<typename T, typename Policy>
bool
sk::util::Holder<T, Policy>::
remove()
{
  if(_slot == 0) {
    return false;
  }
  delete _slot;
  _slot = 0;

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
  get();

  T* object = _slot->deprive();
  remove();
  set(*object);

  return object;
}

#endif /* _SK_UTIL_HOLDER_CXX_ */
