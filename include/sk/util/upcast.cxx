/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_UPCAST_CXX_
#define _SK_UTIL_UPCAST_CXX_

#include <sk/util/upcast.hxx>
#include <sk/util/ClassCastException.h>
#include <sk/util/Class.h>

template<typename U, typename T>
const U&
sk::util::
upcast(const T& object, const sk::util::String& name)
{
  const U* super = dynamic_cast<const U*>(&object);
  if(super == 0) {
    throw sk::util::ClassCastException(name);
  }
  return *super;
}

template<typename U, typename T>
U&
sk::util::
upcast(T& object, const sk::util::String& name)
{
  U* super = dynamic_cast<U*>(&object);
  if(super == 0) {
    throw sk::util::ClassCastException(name);
  }
  return *super;
}

template<typename U>
const U&
sk::util::
upcast(const sk::util::Object& object)
{
  return upcast<U>(object, object.getClass().getName());
}

template<typename U>
U&
sk::util::
upcast(sk::util::Object& object)
{
  return upcast<U>(object, object.getClass().getName());
}

#endif /* _SK_UTIL_UPCAST_CXX_ */
