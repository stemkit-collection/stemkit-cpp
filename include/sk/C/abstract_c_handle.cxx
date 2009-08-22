/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACT_C_HANDLE_CXX_
#define _SK_UTIL_ABSTRACT_C_HANDLE_CXX_

#include <sk/util/abstract_c_handle.hxx>

template<class T>
sk::util::abstract_c_handle<T>::
abstract_c_handle(T& object)
  : _object(&object), _deletable(false)
{
}

template<class T>
sk::util::abstract_c_handle<T>::
abstract_c_handle(T* object)
  : _object(object), _deletable(true)
{
}

template<class T>
sk::util::abstract_c_handle<T>::
~abstract_c_handle()
{
  if(_deletable == true) {
    delete _object;
  }
}

template<class T>
T&
sk::util::abstract_c_handle<T>::
get() const
{
  return *_object;
}

#endif /* _SK_UTIL_ABSTRACT_C_HANDLE_CXX_ */
