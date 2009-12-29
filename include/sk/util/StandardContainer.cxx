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
#include <sk/util/AbstractList.cxx>
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
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
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
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
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
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
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
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
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
  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.push_back(item);
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T& object)
{
  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.push_back(item);
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T* object)
{
  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.push_back(item);
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
remove(const T& object)
{
  return remove(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
remove(const Selector<T>& selector)
{
  typename Type::container_t::iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    return false;
  }
  Policy::clearSlot(*iterator);
  _container.erase(iterator);

  return true;
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const T& object)
{
  return cutoff(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const Selector<T>& selector)
{
  typename Type::container_t::iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  T* object = Policy::depriveObject(*iterator);
  _container.erase(iterator);

  return object;
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(const T& object)
{
  return release(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(const Selector<T>& selector)
{
  typename Type::container_t::iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    throw sk::util::NoSuchElementException(SK_METHOD);
  }
  typename Type::item_t& item = *iterator;
  T* object = Policy::depriveObject(item);
  Policy::setObject(item, *object);

  return object;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Collection<T>& other)
{
  return removeAll(selector::Belongs<T>(other, assessor::EqualPointers<T>()));
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(selector::Belongs<T>(other, assessor));
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
removeAll(const Selector<T>& selector)
{
  bool modified = false;
  typename Type::container_t::iterator iterator = _container.begin(); 
  while(iterator != _container.end()) {
    if(selector.assess(Policy::getObject(*iterator)) == true) {
      Policy::clearSlot(*iterator);
      iterator = _container.erase(iterator);
      modified = true;
    }
    else {
      ++iterator;
    }
  }
  return modified;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Collection<T>& other)
{
  return retainAll(other, assessor::EqualPointers<T>());
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Collection<T>& other, const sk::util::BinaryAssessor<T>& assessor)
{
  return removeAll(sk::util::selector::Not<T>(sk::util::selector::Belongs<T>(other, assessor)));
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
retainAll(const Selector<T>& selector)
{
  return removeAll(sk::util::selector::Not<T>(selector));
}

template<typename T, typename Policy, typename Type>
typename Type::container_t::iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int size)
{
  sk::util::AbstractList<T, Policy>::ensureIndex(index, size);
  typename Type::container_t::iterator iterator = _container.begin();
  while(index--) {
    ++iterator;
  }
  return iterator;
}

template<typename T, typename Policy, typename Type>
typename Type::container_t::const_iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int size) const
{
  sk::util::AbstractList<T, Policy>::ensureIndex(index, size);
  typename Type::container_t::const_iterator iterator = _container.begin();
  while(index--) {
    ++iterator;
  }
  return iterator;
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, const T& object)
{
  typename Type::container_t::iterator iterator = position(index, size() + 1);

  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(iterator, item);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T& object)
{
  typename Type::container_t::iterator iterator = position(index, size() + 1);

  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(iterator, item);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T* object)
{
  typename Type::container_t::iterator iterator = position(index, size() + 1);

  typename Type::item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(iterator, item);
}

template<typename T, typename Policy, typename Type>
const T& 
sk::util::StandardContainer<T, Policy, Type>::
get(int index) const
{
  return Policy::getObject(*position(index, size()));
}

template<typename T, typename Policy, typename Type>
T& 
sk::util::StandardContainer<T, Policy, Type>::
getMutable(int index)
{
  return Policy::getMutableObject(*position(index, size()));
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
indexOf(const T& object) const
{
  return indexOf(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
indexOf(const Selector<T>& selector) const
{
  typename Type::container_t::const_iterator iterator = _container.begin();
  for(int index=0; iterator != _container.end(); ++index, ++iterator) {
    if(selector.assess(Policy::getObject(*iterator)) == true) {
      return index;
    }
  }
  return -1;
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
lastIndexOf(const T& object) const
{
  return lastIndexOf(sk::util::selector::EqualPointer<T>(object));
}

template<typename T, typename Policy, typename Type>
int 
sk::util::StandardContainer<T, Policy, Type>::
lastIndexOf(const Selector<T>& selector) const
{
  typename Type::container_t::const_reverse_iterator iterator = _container.rbegin();
  for(int index=0; iterator != _container.rend(); ++index, ++iterator) {
    if(selector.assess(Policy::getObject(*iterator)) == true) {
      return size() - index - 1;
    }
  }
  return -1;
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
remove(int index)
{
  typename Type::container_t::iterator iterator = position(index, size());
  Policy::clearSlot(*iterator);
  _container.erase(iterator);
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
cutoff(int index)
{
  typename Type::container_t::iterator iterator = position(index, size());
  T* object = Policy::depriveObject(*iterator);
  _container.erase(iterator);

  return object;
}

template<typename T, typename Policy, typename Type>
T* 
sk::util::StandardContainer<T, Policy, Type>::
release(int index)
{
  typename Type::container_t::iterator iterator = position(index, size());
  typename Type::item_t& item = *iterator;
  T* object = Policy::depriveObject(item);
  Policy::setObject(item, *object);

  return object;
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
