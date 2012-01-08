/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_INSPECT_CXX_
#define _SK_UTIL_INSPECT_CXX_

#include <sstream>
#include <sk/util/String.h>

template<typename T>
const sk::util::String
sk::util::inspect(const T* data)
{
  const void* const_void_data = data;
  return sk::util::inspect(const_void_data);
}

template<typename T>
const sk::util::String
sk::util::inspect(T* data)
{
  const void* const_void_data = data;
  return sk::util::inspect(const_void_data);
}

template<typename T>
const sk::util::String
sk::util::inspect(const T& data)
{
  std::stringstream stream;
  stream << data;

  return stream.str();
}

#endif /* _SK_UTIL_INSPECT_CXX_ */
