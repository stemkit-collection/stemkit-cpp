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
#include <sk/util/IllegalStateException.h>
#include <sk/C/invocator.cxx>

template<class T>
sk::C::abstract_handle<T>::
abstract_handle(T& object)
  : _object(&object), _managed(false), _owner(false)
{
}

template<class T>
sk::C::abstract_handle<T>::
abstract_handle(const sk::util::Mapper<bool, T*>& mapper)
  : _object(0), _managed(true), _owner(true)
{
  bool dummy = true;
  execute(sk::C::invocator<bool, T*>(mapper, dummy, _object));
}

template<class T>
sk::C::abstract_handle<T>::
~abstract_handle()
{
  clear();
}

template<class T>
bool
sk::C::abstract_handle<T>::
isManaged() const
{
  return _managed;
}

template<class T>
void
sk::C::abstract_handle<T>::
clear()
{
  if(_object != 0 && _owner == true) {
    delete _object;
    _object = 0;
  }
}
  
template<class T>
T&
sk::C::abstract_handle<T>::
get() const
{
  if(_object == 0) {
    throw sk::util::IllegalStateException("sk::C::abstract_handle<T>::get(): no object");
  }
  return *_object;
}

template<class T>
T*
sk::C::abstract_handle<T>::
release() 
{
  if(_owner == false) {
    throw sk::util::IllegalStateException("sk::C::abstract_handle<T>::release(): not owner");
  }
  _owner = false;
  return _object;
}

template<class T>
template<typename F, typename R>
R 
sk::C::abstract_handle<T>::
invoke(const sk::util::Mapper<F, R>& mapper) const
{
  R result = 0;
  execute(sk::C::invocator<F, R>(mapper, get(), result));
  return result;
}

#endif /* _SK_C_ABSTRACT_HANDLE_CXX_ */
