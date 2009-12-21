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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/selector/EqualPointer.cxx>
#include <sk/util/selector/Any.cxx>
#include <sk/util/selector/Not.cxx>
#include <sk/util/selector/Belongs.cxx>
#include <sk/util/assessor/EqualPointers.cxx>
#include <sk/util/assessor/Binding.cxx>
#include <sk/util/Break.h>

template<class T>
sk::util::AbstractCollection<T>::
AbstractCollection()
{
}

template<class T>
sk::util::AbstractCollection<T>::
~AbstractCollection()
{
}

template<class T>
const sk::util::Class 
sk::util::AbstractCollection<T>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractCollection");
}

template<class T>
const T& 
sk::util::AbstractCollection<T>::
get(const Selector<T>& selector) const 
{
  sk::util::Holder<const T> holder;
  if(find(holder, selector) == true) {
    return holder.get();
  }
  throw sk::util::NoSuchElementException("get()");
}

template<class T>
T& 
sk::util::AbstractCollection<T>::
getMutable(const Selector<T>& selector)
{
  sk::util::Holder<T> holder;
  if(find(holder, selector) == true) {
    return holder.get();
  }
  throw sk::util::NoSuchElementException("getMutable()");
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
find(sk::util::Holder<const T>& holder, const sk::util::Selector<T>& selector) const
{
  struct Processor : public virtual sk::util::Processor<const T> {
    Processor(sk::util::Holder<const T>& holder, const sk::util::Selector<T>& selector)
      : _holder(holder), _selector(selector) {}

    void process(const T& object) const {
      if(_selector.assess(object) == true) {
        _holder.set(object);
        throw sk::util::Break();
      }
    }
    sk::util::Holder<const T>& _holder;
    const sk::util::Selector<T>& _selector;
  };
  holder.clear();
  forEach(Processor(holder, selector));
  return holder.isEmpty() == false;
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
find(sk::util::Holder<const T>& holder, const Selector<T>& selector)
{
  const sk::util::AbstractCollection<T>& self = *this;
  return self.find(holder, selector);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
find(sk::util::Holder<T>& holder, const Selector<T>& selector)
{
  struct Processor : public virtual sk::util::Processor<T> {
    Processor(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector)
      : _holder(holder), _selector(selector) {}

    void process(T& object) const {
      if(_selector.assess(object) == true) {
        _holder.set(object);
        throw sk::util::Break();
      }
    }
    sk::util::Holder<T>& _holder;
    const sk::util::Selector<T>& _selector;
  };
  holder.clear();
  forEach(Processor(holder, selector));
  return holder.isEmpty() == false;
}

template<class T>
struct sk::util::AbstractCollection<T>::Invocator : public virtual sk::util::Processor<const sk::util::Slot<const T> > {
  Invocator(const sk::util::Processor<const T>& processor)
    : _processor(processor) {}

  void process(const sk::util::Slot<const T>& slot) const {
    _processor.process(slot.get());
  }
  const sk::util::Processor<const T>& _processor;
};

template<class T>
void 
sk::util::AbstractCollection<T>::
forEach(const Processor<const T>& processor) const 
{
  try {
    forEachSlot(Invocator(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<class T>
struct sk::util::AbstractCollection<T>::MutableInvocator : public virtual sk::util::Processor<sk::util::Slot<T> > {
  MutableInvocator(const sk::util::Processor<T>& processor)
    : _processor(processor) {}

  void process(sk::util::Slot<T>& slot) const {
    _processor.process(slot.getMutable());
  }
  const sk::util::Processor<T>& _processor;
};

template<class T>
void 
sk::util::AbstractCollection<T>::
forEach(const Processor<T>& processor) 
{
  try {
    forEachSlot(MutableInvocator(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
isEmpty() const 
{
  return size() == 0;
}

template<class T>
int 
sk::util::AbstractCollection<T>::
size() const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
contains(const T& object) const 
{
  return contains(selector::EqualPointer<T>(object));
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
contains(const Selector<T>& selector) const 
{
  sk::util::Holder<const T> holder;
  return find(holder, selector);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
containsAll(const Collection<T>& other) const 
{
  return containsAll(other, sk::util::assessor::EqualPointers<T>());
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
containsAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) const 
{
  struct Processor : public virtual sk::util::Processor<const T> {
    Processor(const sk::util::Collection<T>& collection, const sk::util::BinaryAssessor<T>& assessor, bool& result)
      : _collection(collection), _assessor(assessor), _result(result) {}

    void process(const T& item) const {
      if(_collection.contains(sk::util::assessor::Binding<T>(item, _assessor)) == false) {
        _result = false;
        throw sk::util::Break();
      }
    }
    const sk::util::Collection<T>& _collection;
    const sk::util::BinaryAssessor<T>& _assessor;
    bool& _result;
  };
  bool result = true;
  other.forEach(Processor(*this, assessor, result));
  return result;
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(const T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T& /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T* /*object*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractCollection<T>::
clear() 
{
  removeAll(sk::util::selector::Any<T>());
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const T& object) 
{
  return remove(selector::EqualPointer<T>(object));
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const Selector<T>& /*selector*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const T& object) 
{
  return cutoff(selector::EqualPointer<T>(object));
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const Selector<T>& /*selector*/) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const T& object) 
{
  return release(selector::EqualPointer<T>(object));
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const Selector<T>& selector) 
{
  sk::util::Holder<T> holder(cutoff(selector));
  add(holder.get());

  return holder.release();
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const Collection<T>& other) 
{
  return removeAll(other, sk::util::assessor::EqualPointers<T>());
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const sk::util::Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(sk::util::selector::Belongs<T>(other, assessor));
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
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

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Collection<T>& other) 
{
  return retainAll(other, sk::util::assessor::EqualPointers<T>());
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(sk::util::selector::Not<T>(sk::util::selector::Belongs<T>(other, assessor)));
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Selector<T>& selector) 
{
  return removeAll(sk::util::selector::Not<T>(selector));
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_CXX_ */
