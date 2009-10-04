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
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/selector/Same.cxx>

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
T& 
sk::util::AbstractCollection<T>::
get(const Selector<T>& selector) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractCollection<T>::
forEach(const Processor<T>& procesor) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
find(sk::util::Holder<T>& holder, const Selector<T>& selector) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
isEmpty() const 
{
  throw UnsupportedOperationException(SK_METHOD);
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
  return contains(selector::Same<T>(object));
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
contains(const Selector<T>& selector) const 
{
  sk::util::Holder<T> holder;
  return find(holder, selector);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
containsAll(const Collection<T>& other) const 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T& object) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
add(T* object) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
addAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
moveAll(Collection<T>& other) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
void 
sk::util::AbstractCollection<T>::
clear() 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const T& object) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
remove(const Selector<T>& selector) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const T& object) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
cutoff(const Selector<T>& selector) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const T& object) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
T* 
sk::util::AbstractCollection<T>::
release(const Selector<T>& selector) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
removeAll(const Selector<T>& selector) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Collection<T>& other) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

template<class T>
bool 
sk::util::AbstractCollection<T>::
retainAll(const Selector<T>& selector) 
{
  throw UnsupportedOperationException(SK_METHOD);
}

#endif /* _SK_UTIL_ABSTRACTCOLLECTION_CXX_ */
