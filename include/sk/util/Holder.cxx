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

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>::
Holder()
  : _slot(0)
{
}

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>::
Holder(T& object)
  : _slot(0)
{
  set(object);
}

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>::
Holder(T* object)
  : _slot(0)
{
  set(object);
}

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>::
~Holder()
{
  remove();
}

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>&
sk::util::Holder<T, Policy, SlotActions>::
set(T& object)
{
  remove();
  _slot = new ReferenceSlot<T, SlotActions>(object);
  return *this;
}

template<typename T, typename Policy, typename SlotActions>
sk::util::Holder<T, Policy, SlotActions>&
sk::util::Holder<T, Policy, SlotActions>::
set(T* object)
{
  remove();
  if(object != 0) {
    _slot = new PointerSlot<T, SlotActions>(object);
  }
  return *this;
}

template<typename T, typename Policy, typename SlotActions>
T&
sk::util::Holder<T, Policy, SlotActions>::
get() const
{
  if(_slot == 0) {
    throw MissingResourceException("sk::util::Holder#get()");
  }
  return _slot->get();
}

template<typename T, typename Policy, typename SlotActions>
bool
sk::util::Holder<T, Policy, SlotActions>::
isOwner() const
{
  if(_slot == 0) {
    throw MissingResourceException("sk::util::Holder#isOwner()");
  }
  return _slot->isOwner();
}

template<typename T, typename Policy, typename SlotActions>
bool
sk::util::Holder<T, Policy, SlotActions>::
isEmpty() const
{
  return _slot==0 ? true : false;
}

template<typename T, typename Policy, typename SlotActions>
bool
sk::util::Holder<T, Policy, SlotActions>::
contains(const T& object) const
{
  if(_slot == 0) {
    return false;
  }
  return &_slot->get() == &object ? true : false;
}

template<typename T, typename Policy, typename SlotActions>
bool
sk::util::Holder<T, Policy, SlotActions>::
remove()
{
  if(_slot == 0) {
    return false;
  }
  delete _slot;
  _slot = 0;

  return true;
}

template<typename T, typename Policy, typename SlotActions>
void
sk::util::Holder<T, Policy, SlotActions>::
clear()
{
  remove();
}

template<typename T, typename Policy, typename SlotActions>
T*
sk::util::Holder<T, Policy, SlotActions>::
release()
{
  get();

  T* object = _slot->deprive();
  remove();
  set(*object);

  return object;
}

#endif /* _SK_UTIL_HOLDER_CXX_ */
