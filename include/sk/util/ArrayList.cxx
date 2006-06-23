/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ARRAYLIST_CXX_
#define _SK_UTIL_ARRAYLIST_CXX_

#include <sk/util/ArrayList.hxx>
#include <sk/util/AbstractList.cxx>

template<class T>
sk::util::ArrayList<T>::
ArrayList()
{
}

template<class T>
sk::util::ArrayList<T>::
~ArrayList()
{
  (*this).clear();
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
  _container.clear();
}

#endif /* _SK_UTIL_ARRAYLIST_CXX_ */
