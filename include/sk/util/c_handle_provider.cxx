/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_C_HANDLE_PROVIDER_CXX_
#define _SK_UTIL_C_HANDLE_PROVIDER_CXX_

#include <sk/util/c_handle_provider.hxx>

template<typename T, typename H>
sk::util::c_handle_provider<T, H>::
c_handle_provider(T& object)
  : _handle(new H(object))
{
}

template<typename T, typename H>
sk::util::c_handle_provider<T, H>::
~c_handle_provider()
{
  delete _handle;
}

template<typename T, typename H>
H*
sk::util::c_handle_provider<T, H>::
get_c_handle()
{
  return _handle;
}

template<typename T, typename H>
const H*
sk::util::c_handle_provider<T, H>::
get_c_handle() const
{
  return _handle;
}

template<typename T, typename H>
char* 
sk::util::c_handle_provider<T, H>::
copy(const std::string& s, char* buffer, int size)
{
  if(buffer == 0 || size <= 0) {
    abort();
  }
  strncpy(buffer, s.c_str(), size);
  buffer[size-1] = 0;

  return buffer;
}

#endif /* _SK_UTIL_C_HANDLE_PROVIDER_CXX_ */
