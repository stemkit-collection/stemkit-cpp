/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STANDARDCONTAINER_CXX_
#define _SK_UTIL_STANDARDCONTAINER_CXX_

#include <sk/util/Class.h>
#include <sk/util/StandardContainer.hxx>
#include <sk/util/StreamLiner.h>
#include <sk/util/Break.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/selector/EqualPointer.hxx>
#include <sk/util/selector/Not.hxx>
#include <sk/util/selector/Belongs.hxx>
#include <sk/util/assessor/EqualPointers.hxx>
#include <algorithm>

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>::
StandardContainer()
{
}

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>::
~StandardContainer()
{
  sk::util::Exception::guard(StreamLiner(std::cerr), *this, &StandardContainer<T, Policy, Type>::clear, __FUNCTION__);
}

template<typename T, typename Policy, typename Type>
const sk::util::Class 
sk::util::StandardContainer<T, Policy, Type>::
getClass() const
{
  return sk::util::Class("sk::util::StandardContainer");
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
isEmpty() const
{
  return _container.empty() == true;
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
size() const
{
  return _container.size();
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::Cleaner : std::unary_function<typename Type::item_t, void> {
  void operator()(typename Type::item_t& item) {
    Policy::clearSlot(item);
  }
};

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
clear()
{
  std::for_each(_container.begin(), _container.end(), Cleaner());
  return _container.clear();
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::SelectingFunctor : std::unary_function<typename Type::item_t, bool> {
  SelectingFunctor(const sk::util::Selector<T>& selector)
    : _selector(selector) {}

  bool operator()(const typename Type::item_t& item) {
    return _selector.assess(Policy::getObject(item));
  }
  const sk::util::Selector<T>& _selector;
};

template<typename T, typename Policy, typename Type>
const T& 
sk::util::StandardContainer<T, Policy, Type>::
get(const Selector<T>& selector) const
{
  typename container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return Policy::getObject(*iterator);
}

template<typename T, typename Policy, typename Type>
T& 
sk::util::StandardContainer<T, Policy, Type>::
getMutable(const Selector<T>& selector)
{
  typename container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  return Policy::getMutableObject(*iterator);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
find(sk::util::Holder<T>& holder, const Selector<T>& selector) const
{
  typename container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    return false;
  }
  holder.set(Policy::getObject(*iterator));
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
findMutable(sk::util::Holder<T>& holder, const Selector<T>& selector)
{
  typename container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    return false;
  }
  holder.set(Policy::getMutableObject(*iterator));
  return true;
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::ConstProcessingFunctor : std::unary_function<typename Type::item_t, void> {
  ConstProcessingFunctor(const sk::util::Processor<const T>& processor)
    : _processor(processor) {}

  void operator()(const typename Type::item_t& item) const {
    _processor.process(Policy::getObject(item));
  }
  const sk::util::Processor<const T>& _processor;
};

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
forEach(const Processor<const T>& processor) const
{
  try {
    std::for_each(_container.begin(), _container.end(), ConstProcessingFunctor(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::ProcessingFunctor : std::unary_function<typename Type::item_t, void> {
  ProcessingFunctor(const sk::util::Processor<T>& processor)
    : _processor(processor) {}

  void operator()(const typename Type::item_t& item) const {
    _processor.process(Policy::getMutableObject(item));
  }
  const sk::util::Processor<T>& _processor;
};

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
forEach(const Processor<T>& processor)
{
  try {
    std::for_each(_container.begin(), _container.end(), ProcessingFunctor(processor));
  }
  catch(const sk::util::Break& event) {}
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
contains(const T& object) const
{
  return std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector::EqualPointer<T>(object))) != _container.end();
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
contains(const Selector<T>& selector) const
{
  return std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector)) != _container.end();
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
containsAll(const Collection<T>& other) const
{
  return containsAll(other, assessor::EqualPointers<T>());
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
containsAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor) const
{
  return other.contains(selector::Not<T>(selector::Belongs<T>(*this, assessor))) == false;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(const T& object) 
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T* object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
remove(const T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
remove(const Selector<T>& selector)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const Selector<T>& selector)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(const T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(const Selector<T>& selector)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Collection<T>& other)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Selector<T>& selector)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Collection<T>& other)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Selector<T>& selector)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, const T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T* object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
const T& 
sk::util::StandardContainer<T, Policy, Type>::
get(int index) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T& 
sk::util::StandardContainer<T, Policy, Type>::
getMutable(int index)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
indexOf(const T& object) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
indexOf(const Selector<T>& selector) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
lastIndexOf(const T& object) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
lastIndexOf(const Selector<T>& selector) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
remove(int index)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(int index)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(int index)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, const T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T& object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T* object)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
sort()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
shuffle()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
reverse()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
inspect() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
toString() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

#endif /* _SK_UTIL_STANDARDCONTAINER_CXX_ */
