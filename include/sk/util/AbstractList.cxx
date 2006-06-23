/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACTLIST_CXX_
#define _SK_UTIL_ABSTRACTLIST_CXX_

#include <sk/util/AbstractList.hxx>
#include <sk/util/AbstractCollection.cxx>
#include <sk/util/UnsupportedOperationException.h>

template<class T>
sk::util::AbstractList<T>::
AbstractList()
{
}

template<class T>
sk::util::AbstractList<T>::
~AbstractList()
{
}

template<class T>
const sk::util::Class 
sk::util::AbstractList<T>::
getClass() const
{
  return sk::util::Class("sk::util::AbstractList");
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int index, T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::add(index, object&)");
}

template<class T>
void 
sk::util::AbstractList<T>::
add(int index, T* object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::add(index, object*)");
}

template<class T>
bool 
sk::util::AbstractList<T>::
addAll(int index, const Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::addAll(index, collection)");
}

template<class T>
bool 
sk::util::AbstractList<T>::
moveAll(int index, Collection<T>& other) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::moveAll(index, collection)");
}

template<class T>
T& 
sk::util::AbstractList<T>::
get(int index) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::get(index)");
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const T& object) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::indexOf(object)");
}

template<class T>
int 
sk::util::AbstractList<T>::
indexOf(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::indexOf(selector)");
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const T& object) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(object)");
}

template<class T>
int 
sk::util::AbstractList<T>::
lastIndexOf(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException("sk::util::AbstractList::lastIndexOf(selector)");
}

template<class T>
T& 
sk::util::AbstractList<T>::
remove(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::remove(index)");
}

template<class T>
T* 
sk::util::AbstractList<T>::
cutoff(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::cutoff(index)");
}

template<class T>
T* 
sk::util::AbstractList<T>::
release(int index) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::release(index)");
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T& object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::set(index, object&)");
}

template<class T>
void 
sk::util::AbstractList<T>::
set(int index, T* object) 
{
  throw UnsupportedOperationException("sk::util::AbstractList::set(index, object*)");
}

#endif /* _SK_UTIL_ABSTRACTLIST_CXX_ */
