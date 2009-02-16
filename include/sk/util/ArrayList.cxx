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
#include <sk/util/Slot.hxx>
#include <sk/util/slot/Reference.cxx>
#include <sk/util/slot/Pointer.cxx>
#include <sk/util/StreamLiner.h>
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

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
