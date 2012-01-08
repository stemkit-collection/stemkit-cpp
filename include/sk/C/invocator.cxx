/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_INVOCATOR_CXX_
#define _SK_C_INVOCATOR_CXX_

#include <sk/C/invocator.hxx>

template<typename T, typename R>
sk::C::invocator<T, R>::
invocator(const sk::util::Mapper<T, R>& mapper, T& object, R& result)
  : _mapper(mapper), _object(object), _result(result)
{
}

template<typename T, typename R>
sk::C::invocator<T, R>::
~invocator()
{
}

template<typename T, typename R>
void
sk::C::invocator<T, R>::
run() const
{
  _result = _mapper.map(_object);
}

#endif /* _SK_C_INVOCATOR_CXX_ */
