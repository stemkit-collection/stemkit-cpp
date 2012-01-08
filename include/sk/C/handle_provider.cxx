/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_HANDLE_PROVIDER_CXX_
#define _SK_C_HANDLE_PROVIDER_CXX_

#include <sk/C/handle_provider.hxx>

template<typename T, typename H>
sk::C::handle_provider<T, H>::
handle_provider(T& object)
  : _handle(new H(object))
{
}

template<typename T, typename H>
sk::C::handle_provider<T, H>::
~handle_provider()
{
  delete _handle;
}

template<typename T, typename H>
H*
sk::C::handle_provider<T, H>::
get_c_handle()
{
  return _handle;
}

template<typename T, typename H>
const H*
sk::C::handle_provider<T, H>::
get_c_handle() const
{
  return _handle;
}

#endif /* _SK_C_HANDLE_PROVIDER_CXX_ */
