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
#include <sk/util/Holder.cxx>
#include <sk/util/StreamLiner.h>
#include <sk/util/Break.h>
#include <sk/util/Validator.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/selector/Not.hxx>
#include <sk/util/selector/Belongs.hxx>
#include <sk/util/assessor/EqualPointers.hxx>
#include <sk/util/assessor/LessValues.hxx>
#include <sk/util/Lists.hxx>
#include <sk/util/Collections.hxx>
#include <sk/util/OpenEndedLists.hxx>

#include <algorithm>
#include <iostream>
#include <functional>

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>::
StandardContainer()
{
}

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>::
StandardContainer(const sk::util::StandardContainer<T, Policy, Type>& other)
{
  Policy::copyCollection(*this, other);
}

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>::
~StandardContainer()
{
  sk::util::Exception::guard(StreamLiner(std::cerr), *this, &StandardContainer<T, Policy, Type>::clear, __FUNCTION__);
}

template<typename T, typename Policy, typename Type>
sk::util::StandardContainer<T, Policy, Type>&
sk::util::StandardContainer<T, Policy, Type>::
operator = (const sk::util::StandardContainer<T, Policy, Type>& other)
{
  clear();
  Policy::copyCollection(*this, other);
  return *this;
}

template<typename T, typename Policy, typename Type>
const sk::util::Class
sk::util::StandardContainer<T, Policy, Type>::
getClass() const
{
  return sk::util::Class("sk::util::StandardContainer");
}

template<typename T, typename Policy, typename Type>
inline void
sk::util::StandardContainer<T, Policy, Type>::
add(typename Type::container_t::iterator position, typename Policy::slot_storage_t storage)
{
  _container.insert(position, storage);
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::iterator
sk::util::StandardContainer<T, Policy, Type>::
remove(typename Type::container_t::iterator position)
{
  Policy::clearSlot(*position);
  return _container.erase(position);
}

template<typename T, typename Policy, typename Type>
inline T*
sk::util::StandardContainer<T, Policy, Type>::
cutoff(typename Type::container_t::iterator position)
{
  T* object = Policy::depriveObject(*position);
  _container.erase(position);

  return object;
}

template<typename T, typename Policy, typename Type>
inline T*
sk::util::StandardContainer<T, Policy, Type>::
release(typename Type::container_t::iterator position)
{
  T* object = Policy::depriveObject(*position);
  Policy::setObject(*position, *object);

  return object;
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
struct sk::util::StandardContainer<T, Policy, Type>::Cleaner : std::unary_function<typename Policy::slot_storage_t, void> {
  void operator()(typename Policy::slot_storage_t& storage) {
    Policy::clearSlot(storage);
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
struct sk::util::StandardContainer<T, Policy, Type>::SelectingFunctor : std::unary_function<typename Policy::slot_storage_t, bool> {
  SelectingFunctor(const sk::util::Selector<T>& selector)
    : _selector(selector) {}

  bool operator()(const typename Policy::slot_storage_t& storage) {
    return _selector.assess(Policy::getObject(storage));
  }
  const sk::util::Selector<T>& _selector;
};

template<typename T, typename Policy, typename Type>
const T&
sk::util::StandardContainer<T, Policy, Type>::
get(const Selector<T>& selector) const
{
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  sk::util::Validator::ensureElement(iterator != _container.end());

  return Policy::getObject(*iterator);
}

template<typename T, typename Policy, typename Type>
T&
sk::util::StandardContainer<T, Policy, Type>::
getMutable(const Selector<T>& selector) const
{
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  sk::util::Validator::ensureElement(iterator != _container.end());

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
findMutable(sk::util::Holder<T>& holder, const Selector<T>& selector) const
{
  typename Type::container_t::const_iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  if(iterator == _container.end()) {
    return false;
  }
  holder.set(Policy::getMutableObject(*iterator));
  return true;
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::ConstProcessingFunctor : std::unary_function<typename Policy::slot_storage_t, void> {
  ConstProcessingFunctor(const sk::util::Processor<const T>& processor)
    : _processor(processor) {}

  void operator()(const typename Policy::slot_storage_t& storage) const {
    _processor.process(Policy::getObject(storage));
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
struct sk::util::StandardContainer<T, Policy, Type>::ProcessingFunctor : std::unary_function<typename Policy::slot_storage_t, void> {
  ProcessingFunctor(const sk::util::Processor<T>& processor)
    : _processor(processor) {}

  void operator()(const typename Policy::slot_storage_t& storage) const {
    _processor.process(Policy::getMutableObject(storage));
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
  return std::find_if(_container.begin(), _container.end(), SelectingFunctor(typename Policy::equal_selector_t(object))) != _container.end();
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
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
  return true;
}

template<typename T, typename Policy, typename Type>
bool
sk::util::StandardContainer<T, Policy, Type>::
add(T& object)
{
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
  return true;
}

template<typename T, typename Policy, typename Type>
bool
sk::util::StandardContainer<T, Policy, Type>::
add(T* object)
{
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
  return true;
}

template<typename T, typename Policy, typename Type>
bool
sk::util::StandardContainer<T, Policy, Type>::
remove(const T& object)
{
  return remove(typename Policy::equal_selector_t(object));
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
  remove(iterator);
  return true;
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const T& object)
{
  return cutoff(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoff(const Selector<T>& selector)
{
  typename Type::container_t::iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  sk::util::Validator::ensureElement(iterator != _container.end());

  return cutoff(iterator);
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
release(const T& object)
{
  return release(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
release(const Selector<T>& selector)
{
  typename Type::container_t::iterator iterator = std::find_if(_container.begin(), _container.end(), SelectingFunctor(selector));
  sk::util::Validator::ensureElement(iterator != _container.end());

  return release(iterator);
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
      iterator = remove(iterator);
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
int
sk::util::StandardContainer<T, Policy, Type>::
indexOf(const T& object) const
{
  return indexOf(typename Policy::equal_selector_t(object));
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
  return lastIndexOf(typename Policy::equal_selector_t(object));
}

template<typename T, typename Policy, typename Type>
int
sk::util::StandardContainer<T, Policy, Type>::
lastIndexOf(const Selector<T>& selector) const
{
  typename Type::container_t::const_reverse_iterator iterator = _container.rbegin();
  for(int index=0; iterator != _container.rend(); ++index, ++iterator) {
    if(selector.assess(Policy::getObject(*iterator)) == true) {
      return _container.size() - index - 1;
    }
  }
  return -1;
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int tailOffset)
{
  sk::util::Validator::ensureIndex(index, _container.size() + tailOffset);
  typename Type::container_t::iterator iterator = _container.begin();
  while(index--) {
    ++iterator;
  }
  return iterator;
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::const_iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int tailOffset) const
{
  sk::util::Validator::ensureIndex(index, _container.size() + tailOffset);
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
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T& object)
{
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T* object)
{
  add(position(index, 1), Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
const T&
sk::util::StandardContainer<T, Policy, Type>::
get(int index) const
{
  return Policy::getObject(*position(index, 0));
}

template<typename T, typename Policy, typename Type>
T&
sk::util::StandardContainer<T, Policy, Type>::
getMutable(int index) const
{
  return Policy::getMutableObject(*position(index, 0));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
remove(int index)
{
  remove(position(index, 0));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoff(int index)
{
  return cutoff(position(index, 0));
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
release(int index)
{
  return release(position(index, 0));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
set(int index, const T& object)
{
  Policy::setObject(*position(index, 0) , object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T& object)
{
  Policy::setObject(*position(index, 0) , object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T* object)
{
  Policy::setObject(*position(index, 0) , object);
}

template<typename T, typename Policy, typename Type>
struct sk::util::StandardContainer<T, Policy, Type>::AssessingBinaryFunctor : std::binary_function<typename Policy::slot_storage_t, typename Policy::slot_storage_t, void> {
  AssessingBinaryFunctor(const sk::util::BinaryAssessor<T>& assessor)
    : _assessor(assessor) {}

  bool operator()(const typename Policy::slot_storage_t first, const typename Policy::slot_storage_t second) const {
    return _assessor.assess(Policy::getObject(first), Policy::getObject(second));
  }
  const sk::util::BinaryAssessor<T>& _assessor;
};

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
sort()
{
  sort(assessor::LessValues<T>());
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
  std::reverse(_container.begin(), _container.end());
}

template<typename T, typename Policy, typename Type>
const sk::util::String
sk::util::StandardContainer<T, Policy, Type>::
inspect() const
{
  sk::util::String depot;
  int index;

  typename sk::util::Lists<T, Policy>::SlotInspector inspector(depot, index);
  std::for_each(_container.begin(), _container.end(), inspector);

  return inspector.collect();
}

template<typename T, typename Policy, typename Type>
const sk::util::String
sk::util::StandardContainer<T, Policy, Type>::
toString() const
{
  return inspect();
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addFirst(const T& object)
{
  add(0, object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addFirst(T& object)
{
  add(0, object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addFirst(T* object)
{
  add(0, object);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addLast(const T& object)
{
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addLast(T& object)
{
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
addLast(T* object)
{
  OpenEndedLists<T, Policy, Type>::addLast(_container, Collections<T, Policy>::makeStorage(object));
}

template<typename T, typename Policy, typename Type>
const T&
sk::util::StandardContainer<T, Policy, Type>::
getFirst() const
{
  sk::util::Validator::ensureNotEmpty(_container.size());
  return Policy::getObject(_container.front());
}

template<typename T, typename Policy, typename Type>
const T&
sk::util::StandardContainer<T, Policy, Type>::
getLast() const
{
  sk::util::Validator::ensureNotEmpty(_container.size());
  return Policy::getObject(_container.back());
}

template<typename T, typename Policy, typename Type>
T&
sk::util::StandardContainer<T, Policy, Type>::
getMutableFirst() const
{
  sk::util::Validator::ensureNotEmpty(_container.size());
  return Policy::getMutableObject(_container.front());
}

template<typename T, typename Policy, typename Type>
T&
sk::util::StandardContainer<T, Policy, Type>::
getMutableLast() const
{
  sk::util::Validator::ensureNotEmpty(_container.size());
  return Policy::getMutableObject(_container.back());
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
removeFirst()
{
  OpenEndedLists<T, Policy, Type>::removeFirstGeneric(_container);
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
removeLast()
{
  OpenEndedLists<T, Policy, Type>::removeLast(_container);
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoffFirst()
{
  return OpenEndedLists<T, Policy, Type>::cutoffFirstGeneric(_container);
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoffLast()
{
  return OpenEndedLists<T, Policy, Type>::cutoffLast(_container);
}

template<typename T, typename Policy, typename Type>
const sk::util::String
sk::util::StandardContainer<T, Policy, Type>::
join(const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper) const
{
  return sk::util::Lists<T, Policy>::join(*this, separator, mapper);
}

template<typename T, typename Policy, typename Type>
const sk::util::String
sk::util::StandardContainer<T, Policy, Type>::
join(const sk::util::String& separator) const
{
  return sk::util::Lists<T, Policy>::join(*this, separator);
}

template<typename T, typename Policy, typename Type>
const sk::util::String
sk::util::StandardContainer<T, Policy, Type>::
join() const
{
  return sk::util::Lists<T, Policy>::join(*this);
}

#endif /* _SK_UTIL_STANDARDCONTAINER_CXX_ */
