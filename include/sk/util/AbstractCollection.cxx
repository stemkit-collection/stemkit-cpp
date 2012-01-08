/*  vim:sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTCOLLECTION_CXX_
#define _SK_UTIL_ABSTRACTCOLLECTION_CXX_

#include <sk/util/AbstractCollection.hxx>
#include <sk/util/Holder.cxx>
#include <sk/util/Validator.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/selector/Any.hxx>
#include <sk/util/selector/Not.hxx>
#include <sk/util/selector/Belongs.hxx>
#include <sk/util/assessor/EqualPointers.hxx>
#include <sk/util/assessor/Binding.hxx>
#include <sk/util/Break.h>

template<typename T, typename Policy>
sk::util::AbstractCollection<T, Policy>::
AbstractCollection()
{
}

template<typename T, typename Policy>
sk::util::AbstractCollection<T, Policy>::
~AbstractCollection()
{
}

template<typename T, typename Policy>
const sk::util::Class
sk::util::AbstractCollection<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractCollection");
}

template<typename T, typename Policy>
const T&
sk::util::AbstractCollection<T, Policy>::
get(const Selector<T>& selector) const
{
  sk::util::Holder<T> holder;
  sk::util::Validator::ensureElement(find(holder, selector));
  return holder.get();
}

template<typename T, typename Policy>
T&
sk::util::AbstractCollection<T, Policy>::
getMutable(const Selector<T>& selector) const
{
  sk::util::Holder<T> holder;
  sk::util::Validator::ensureElement(findMutable(holder, selector));
  return holder.getMutable();
}

template<typename T, typename Policy>
struct sk::util::AbstractCollection<T, Policy>::Finder : public virtual sk::util::Processor<const typename Policy::slot_t> {
  Finder(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector)
    : _holder(holder), _selector(selector) {}

  void process(const typename Policy::slot_t& slot) const {
    const T& object = slot.get();
    if(_selector.assess(object) == true) {
      _holder.set(object);
      throw sk::util::Break();
    }
  }
  sk::util::Holder<T>& _holder;
  const sk::util::Selector<T>& _selector;
};

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
find(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector) const
{
  try {
    forEachSlot(Finder(holder, selector));
    return false;
  }
  catch(const sk::util::Break& event) {}
  return true;
}

template<typename T, typename Policy>
struct sk::util::AbstractCollection<T, Policy>::MutableFinder : public virtual sk::util::Processor<typename Policy::slot_t> {
  MutableFinder(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector)
    : _holder(holder), _selector(selector) {}

  void process(typename Policy::slot_t& slot) const {
    if(_selector.assess(slot.get()) == true) {
      _holder.set(slot.getMutable());
      throw sk::util::Break();
    }
  }
  sk::util::Holder<T>& _holder;
  const sk::util::Selector<T>& _selector;
};

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
findMutable(sk::util::Holder<T>& holder, const Selector<T>& selector) const
{
  try {
    forEachSlot(MutableFinder(holder, selector));
    return false;
  }
  catch(const sk::util::Break& event) {}
  return true;
}

template<typename T, typename Policy>
struct sk::util::AbstractCollection<T, Policy>::Invocator : public virtual sk::util::Processor<const typename Policy::slot_t> {
  Invocator(const sk::util::Processor<const T>& processor)
    : _processor(processor) {}

  void process(const typename Policy::slot_t& slot) const {
    _processor.process(slot.get());
  }
  const sk::util::Processor<const T>& _processor;
};

template<typename T, typename Policy>
void
sk::util::AbstractCollection<T, Policy>::
forEach(const Processor<const T>& processor) const
{
  try {
    forEachSlot(Invocator(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<typename T, typename Policy>
struct sk::util::AbstractCollection<T, Policy>::MutableInvocator : public virtual sk::util::Processor<typename Policy::slot_t> {
  MutableInvocator(const sk::util::Processor<T>& processor)
    : _processor(processor) {}

  void process(typename Policy::slot_t& slot) const {
    _processor.process(slot.getMutable());
  }
  const sk::util::Processor<T>& _processor;
};

template<typename T, typename Policy>
void
sk::util::AbstractCollection<T, Policy>::
forEach(const Processor<T>& processor)
{
  try {
    forEachSlot(MutableInvocator(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
isEmpty() const
{
  return size() == 0;
}

template<typename T, typename Policy>
int
sk::util::AbstractCollection<T, Policy>::
size() const
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
contains(const T& object) const
{
  return contains(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
contains(const Selector<T>& selector) const
{
  sk::util::Holder<T> holder;
  return find(holder, selector);
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
containsAll(const Collection<T>& other) const
{
  return containsAll(other, sk::util::assessor::EqualPointers<T>());
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
containsAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) const
{
  return other.contains(selector::Not<T>(selector::Belongs<T>(*this, assessor))) == false;
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
add(const T& /*object*/)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
add(T& /*object*/)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
add(T* /*object*/)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
void
sk::util::AbstractCollection<T, Policy>::
clear()
{
  removeAll(sk::util::selector::Any<T>());
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
remove(const T& object)
{
  return remove(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
remove(const Selector<T>& /*selector*/)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
T*
sk::util::AbstractCollection<T, Policy>::
cutoff(const T& object)
{
  return cutoff(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy>
T*
sk::util::AbstractCollection<T, Policy>::
cutoff(const Selector<T>& /*selector*/)
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy>
T*
sk::util::AbstractCollection<T, Policy>::
release(const T& object)
{
  return release(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy>
T*
sk::util::AbstractCollection<T, Policy>::
release(const Selector<T>& selector)
{
  sk::util::Holder<T> holder(cutoff(selector));
  add(holder.get());

  return holder.release();
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
removeAll(const Collection<T>& other)
{
  return removeAll(other, sk::util::assessor::EqualPointers<T>());
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
removeAll(const sk::util::Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(sk::util::selector::Belongs<T>(other, assessor));
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
removeAll(const Selector<T>& selector)
{
  bool result = false;
  while(true) {
    if(remove(selector) == false) {
      break;
    }
    result = true;
  }
  return result;
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
retainAll(const Collection<T>& other)
{
  return retainAll(other, sk::util::assessor::EqualPointers<T>());
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(sk::util::selector::Not<T>(sk::util::selector::Belongs<T>(other, assessor)));
}

template<typename T, typename Policy>
bool
sk::util::AbstractCollection<T, Policy>::
retainAll(const Selector<T>& selector)
{
  return removeAll(sk::util::selector::Not<T>(selector));
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_CXX_ */
