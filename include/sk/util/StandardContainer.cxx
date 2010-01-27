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
#include <sk/util/StringArray.h>
#include <sk/util/Break.h>
#include <sk/util/Validator.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/selector/EqualPointer.hxx>
#include <sk/util/selector/Not.hxx>
#include <sk/util/selector/Belongs.hxx>
#include <sk/util/assessor/EqualPointers.hxx>
#include <sk/util/assessor/LessValues.hxx>

#include <sk/util/mapper/Stringing.hxx>
#include <sk/util/Injector.cxx>
#include <sk/util/reducer/Join.hxx>

#include <algorithm>
#include <iostream>

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
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.push_back(storage);
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T& object)
{
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.push_back(storage);
  return true;
}

template<typename T, typename Policy, typename Type>
bool 
sk::util::StandardContainer<T, Policy, Type>::
add(T* object)
{
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.push_back(storage);
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
  sk::util::Validator::ensureElement(iterator != _container.end());

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
  sk::util::Validator::ensureElement(iterator != _container.end());

  typename Policy::slot_storage_t& storage = *iterator;
  T* object = Policy::depriveObject(storage);
  Policy::setObject(storage, *object);

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
inline typename Type::container_t::iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int size)
{
  sk::util::Validator::ensureIndex(index, size);
  typename Type::container_t::iterator iterator = _container.begin();
  while(index--) {
    ++iterator;
  }
  return iterator;
}

template<typename T, typename Policy, typename Type>
inline typename Type::container_t::const_iterator
sk::util::StandardContainer<T, Policy, Type>::
position(int index, int size) const
{
  sk::util::Validator::ensureIndex(index, size);
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

  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.insert(iterator, storage);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T& object)
{
  typename Type::container_t::iterator iterator = position(index, size() + 1);

  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.insert(iterator, storage);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
add(int index, T* object)
{
  typename Type::container_t::iterator iterator = position(index, size() + 1);

  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  _container.insert(iterator, storage);
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
getMutable(int index) const
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
  typename Policy::slot_storage_t& storage = *iterator;
  T* object = Policy::depriveObject(storage);
  Policy::setObject(storage, *object);

  return object;
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, const T& object)
{
  typename Type::container_t::iterator iterator = position(index, size());
  Policy::setObject(*iterator, object);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T& object)
{
  typename Type::container_t::iterator iterator = position(index, size());
  Policy::setObject(*iterator, object);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
set(int index, T* object)
{
  typename Type::container_t::iterator iterator = position(index, size());
  Policy::setObject(*iterator, object);
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
struct sk::util::StandardContainer<T, Policy, Type>::InspectingFunctor : std::unary_function<typename Policy::slot_storage_t, void> {
  InspectingFunctor(sk::util::StringArray& depot)
    : _depot(depot), _index(0) {}

  void operator()(const typename Policy::const_slot_storage_t& storage) const {
    _depot << (sk::util::String::valueOf(_index++) + Policy::inspectSlot(storage));
  }
  sk::util::StringArray& _depot;
  mutable int _index;
};

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
inspect() const
{
  if(isEmpty() == true) {
    return "[]";
  }
  sk::util::StringArray depot;
  std::for_each(_container.begin(), _container.end(), InspectingFunctor(depot));
  return "[" + sk::util::String::valueOf(size()) + ": " + depot.join(", ") + " ]";
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
  add(object);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
addLast(T& object)
{
  add(object);
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
addLast(T* object)
{
  add(object);
}

template<typename T, typename Policy, typename Type>
const T& 
sk::util::StandardContainer<T, Policy, Type>::
getFirst() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return Policy::getObject(_container.front());
}

template<typename T, typename Policy, typename Type>
const T& 
sk::util::StandardContainer<T, Policy, Type>::
getLast() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return Policy::getObject(_container.back());
}

template<typename T, typename Policy, typename Type>
T& 
sk::util::StandardContainer<T, Policy, Type>::
getMutableFirst() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return Policy::getMutableObject(_container.front());
}

template<typename T, typename Policy, typename Type>
T& 
sk::util::StandardContainer<T, Policy, Type>::
getMutableLast() const
{
  sk::util::Validator::ensureNotEmpty(size());
  return Policy::getMutableObject(_container.back());
}

template<typename T, typename Policy, typename Type>
void 
sk::util::StandardContainer<T, Policy, Type>::
removeFirst()
{
  sk::util::Validator::ensureNotEmpty(size());
  Policy::clearSlot(_container.front());
  _container.erase(_container.begin());
}

template<typename T, typename Policy, typename Type>
void
sk::util::StandardContainer<T, Policy, Type>::
removeLast()
{
  sk::util::Validator::ensureNotEmpty(size());
  Policy::clearSlot(_container.back());
  _container.pop_back();
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoffFirst()
{
  sk::util::Validator::ensureNotEmpty(size());
  T* object = Policy::depriveObject(_container.front());
  _container.erase(_container.begin());

  return object;
}

template<typename T, typename Policy, typename Type>
T*
sk::util::StandardContainer<T, Policy, Type>::
cutoffLast()
{
  sk::util::Validator::ensureNotEmpty(size());
  T* object = Policy::depriveObject(_container.back());
  _container.pop_back();

  return object;
}

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
join(const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper) const
{
  return sk::util::Injector<T, sk::util::String>(*this).inject(mapper, sk::util::reducer::Join<T, sk::util::String>(separator));
}

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
join(const sk::util::String& separator) const
{
  return join(separator, sk::util::mapper::Stringing<T>());
}

template<typename T, typename Policy, typename Type>
const sk::util::String 
sk::util::StandardContainer<T, Policy, Type>::
join() const
{
  return join("", sk::util::mapper::Stringing<T>());
}

#endif /* _SK_UTIL_STANDARDCONTAINER_CXX_ */
