/*  vim:sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ARRAYLIST_CXX_
#define _SK_UTIL_ARRAYLIST_CXX_

#include <sk/util/ArrayList.hxx>
#include <sk/util/AbstractList.cxx>
#include <sk/util/Holder.cxx>
#include <sk/util/Slot.hxx>
#include <sk/util/slot/Reference.cxx>
#include <sk/util/slot/Pointer.cxx>
#include <sk/util/StreamLiner.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/slot/BinaryAssessorFunctor.cxx>
#include <sk/util/assessor/LessValues.cxx>
#include <iostream>
#include <algorithm>

template<typename T, typename Policy>
sk::util::ArrayList<T, Policy>::
ArrayList()
{
}

template<typename T, typename Policy>
sk::util::ArrayList<T, Policy>::
~ArrayList()
{
  Exception::guard(StreamLiner(std::cerr), *this, &ArrayList<T, Policy>::clear, __FUNCTION__);
}

template<typename T, typename Policy>
const sk::util::Class
sk::util::ArrayList<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::ArrayList");
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
clear()
{
  for(typename container_t::iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    delete *iterator;
  }
  _container.clear();
}

template<typename T, typename Policy>
int
sk::util::ArrayList<T, Policy>::
size() const 
{
  return _container.size();
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
isEmpty() const
{
  return _container.empty();
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
add(const T& object)
{
  item_t item = 0;
  Policy::setObject(item, object);
  _container.push_back(item);

  return true;
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
add(T& object)
{
  item_t item = 0;
  Policy::setObject(item, object);
  _container.push_back(item);

  return true;
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
add(T* object)
{
  item_t item = 0;
  Policy::setObject(item, object);
  _container.push_back(item);

  return true;
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
add(int index, const T& object)
{
  ensureIndex(index, size() + 1);

  item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(_container.begin() + index, item);
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
add(int index, T& object)
{
  ensureIndex(index, size() + 1);

  item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(_container.begin() + index, item);
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
add(int index, T* object)
{
  ensureIndex(index, size() + 1);

  item_t item = 0;
  Policy::setObject(item, object);

  _container.insert(_container.begin() + index, item);
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
forEachSlot(const sk::util::Processor<const sk::util::Slot<T> >& processor) const
{
  for(typename container_t::const_iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    processor.process(*(*iterator));
  }
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
forEachSlot(const sk::util::Processor<sk::util::Slot<T> >& processor)
{
  for(typename container_t::iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    processor.process(*(*iterator));
  }
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
removeAll(const sk::util::Selector<T>& selector)
{
  int removed = 0;
  typename container_t::iterator iterator = _container.begin();
  while(iterator != _container.end()) {
    if(selector.assess((*iterator)->get())) {
      delete *iterator;
      iterator = _container.erase(iterator);
      ++removed;
    }
    else {
      ++iterator;
    }
  }
  return removed != 0;
}

template<typename T, typename Policy>
bool
sk::util::ArrayList<T, Policy>::
find(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector) const
{
  for(typename container_t::const_iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    if(selector.assess((*iterator)->get()) == true) {
      holder.set((*iterator)->get());
      return true;
    }
  }
  holder.clear();
  return false;
}

template<typename T, typename Policy>
const T& 
sk::util::ArrayList<T, Policy>::
get(int index) const 
{
  ensureIndex(index, size());
  return _container[index]->get();
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
remove(int index) 
{
  ensureIndex(index, size());

  typename container_t::iterator iterator = _container.begin() + index;
  delete *iterator;
  _container.erase(iterator);
}

template<typename T, typename Policy>
T*
sk::util::ArrayList<T, Policy>::
cutoff(int index) 
{
  ensureIndex(index, size());

  T* object = _container[index]->deprive();
  typename container_t::iterator iterator = _container.begin() + index;
  delete *iterator;
  _container.erase(iterator);

  return object;
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
sort()
{
  std::sort(_container.begin(), _container.end(), sk::util::slot::BinaryAssessorFunctor<T>(sk::util::assessor::LessValues<T>()));
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
sort(const sk::util::BinaryAssessor<T>& assessor)
{
  std::sort(_container.begin(), _container.end(), sk::util::slot::BinaryAssessorFunctor<T>(assessor));
}

template<typename T, typename Policy>
void
sk::util::ArrayList<T, Policy>::
shuffle()
{
  std::random_shuffle(_container.begin(), _container.end());
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
