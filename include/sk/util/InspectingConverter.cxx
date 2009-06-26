/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_INSPECTINGCONVERTER_CXX_
#define _SK_UTIL_INSPECTINGCONVERTER_CXX_

#include <sk/util/InspectingConverter.hxx>

template<typename T>
sk::util::InspectingConverter<T>::
InspectingConverter()
{
}

template<typename T>
sk::util::InspectingConverter<T>::
~InspectingConverter()
{
}

template<typename T>
sk::util::String
sk::util::InspectingConverter<T>::
convert(const T& object) const
{
  return object.inspect();
}

#endif /* _SK_UTIL_INSPECTINGCONVERTER_CXX_ */
