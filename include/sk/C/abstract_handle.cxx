/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_C_ABSTRACT_HANDLE_CXX_
#define _SK_C_ABSTRACT_HANDLE_CXX_

#include <sk/C/abstract_handle.hxx>
#include <sk/util/UnsupportedOperationException.h>

template<class T>
sk::C::abstract_handle<T>::
abstract_handle(T& object)
  : _object(&object), _deletable(false)
{
}

template<class T>
sk::C::abstract_handle<T>::
abstract_handle(T* object)
  : _object(object), _deletable(true)
{
}

template<class T>
sk::C::abstract_handle<T>::
abstract_handle(const sk::util::Mapper<bool, T*>& mapper)
  : _object(invoke(mapper)), _deletable(true)
{
}

template<class T>
sk::C::abstract_handle<T>::
~abstract_handle()
{
  if(_deletable == true) {
    delete _object;
  }
}

template<class T>
T&
sk::C::abstract_handle<T>::
get() const
{
  return *_object;
}

template<class T>
template<typename F, typename R>
R 
sk::C::abstract_handle<T>::
invoke(const sk::util::Mapper<F, R>& mapper) const
{
  throw sk::util::UnsupportedOperationException("invoke");
}

#endif /* _SK_C_ABSTRACT_HANDLE_CXX_ */
