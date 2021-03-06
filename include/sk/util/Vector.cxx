/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_VECTOR_CXX_
#define _SK_UTIL_VECTOR_CXX_

#include <sk/util/Class.h>
#include <sk/util/Vector.hxx>
#include <sk/util/RandomAccessContainer.cxx>

template<typename T, typename Policy>
sk::util::Vector<T, Policy>::
Vector()
{
}

template<typename T, typename Policy>
sk::util::Vector<T, Policy>::
~Vector()
{
}

template<typename T, typename Policy>
const sk::util::Class
sk::util::Vector<T, Policy>::
getClass() const
{
  return sk::util::Class("sk::util::Vector");
}

#endif /* _SK_UTIL_VECTOR_CXX_ */
