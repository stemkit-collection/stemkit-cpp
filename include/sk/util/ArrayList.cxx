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
#include <iostream>

template<class T>
sk::util::ArrayList<T>::
ArrayList()
{
}

template<class T>
sk::util::ArrayList<T>::
~ArrayList()
{
  Exception::guard(StreamLiner(std::cerr), *this, &ArrayList<T>::clear, __FUNCTION__);
}

template<class T>
const sk::util::Class
sk::util::ArrayList<T>::
getClass() const
{
  return sk::util::Class("sk::util::ArrayList");
}

template<class T>
void
sk::util::ArrayList<T>::
clear()
{
  for(typename container::iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    delete *iterator;
  }
  _container.clear();
}

template<class T>
int
sk::util::ArrayList<T>::
size() const 
{
  return _container.size();
}

template<class T>
bool
sk::util::ArrayList<T>::
isEmpty() const
{
  return _container.empty();
}

template<class T>
bool
sk::util::ArrayList<T>::
add(T& object)
{
  _container.push_back(new slot::Reference<T>(object));
  return true;
}

template<class T>
bool
sk::util::ArrayList<T>::
add(T* object)
{
  _container.push_back(new slot::Pointer<T>(object));
  return true;
}

template<class T>
void
sk::util::ArrayList<T>::
forEachSlot(const sk::util::SlotProcessor<T>& processor) const
{
  for(typename container::const_iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    processor.process(*(*iterator));
  }
}

template<class T>
bool
sk::util::ArrayList<T>::
removeAll(const sk::util::Selector<T>& selector)
{
  int removed = 0;
  typename container::iterator iterator = _container.begin();
  while(iterator != _container.end()) {
    if(selector.assess((*iterator)->get())) {
      iterator = _container.erase(iterator);
      ++removed;
    }
    else {
      ++iterator;
    }
  }
  return removed != 0;
}

template<class T>
bool
sk::util::ArrayList<T>::
find(sk::util::Holder<T>& holder, const sk::util::Selector<T>& selector) const
{
  for(typename container::const_iterator iterator = _container.begin(); iterator != _container.end() ; ++iterator) {
    if(selector.assess((*iterator)->get()) == true) {
      holder.set((*iterator)->get());
      return true;
    }
  }
  holder.clear();
  return false;
}

template<class T>
T& 
sk::util::ArrayList<T>::
get(int index) const 
{
  if((index < 0) || (index >= _container.size())) {
    throw sk::util::IndexOutOfBoundsException("sk::util::ArrayList<T>#get(), index=" + sk::util::String::valueOf(index) + ", size=" + sk::util::String::valueOf(_container.size()));
  }
  return _container[index]->get();
}

template<class T>
void
sk::util::ArrayList<T>::
remove(int index) 
{
  if((index < 0) || (index >= _container.size())) {
    throw sk::util::IndexOutOfBoundsException("sk::util::ArrayList<T>#remove(), index=" + sk::util::String::valueOf(index) + ", size=" + sk::util::String::valueOf(_container.size()));
  }
  _container.erase(_container.begin() + index);
}

template<class T>
T*
sk::util::ArrayList<T>::
cutoff(int index) 
{
  if((index < 0) || (index >= _container.size())) {
    throw sk::util::IndexOutOfBoundsException("sk::util::ArrayList<T>#remove(), index=" + sk::util::String::valueOf(index) + ", size=" + sk::util::String::valueOf(_container.size()));
  }
  T* object = _container[index]->deprive();
  _container.erase(_container.begin() + index);

  return object;
}

namespace {
  template<typename T>
  struct SlotComparator {
    bool operator()(const sk::util::Slot<T>* first, const sk::util::Slot<T>* second) {
      return first->get() < second->get();
    }
  };
}

template<class T>
void
sk::util::ArrayList<T>::
sort()
{
  std::sort(_container.begin(), _container.end(), SlotComparator<T>());
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
