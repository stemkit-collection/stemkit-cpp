/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_CLONINGPROCESSOR_CXX_
#define _SK_UTIL_CLONINGPROCESSOR_CXX_

#include <sk/util/CloningProcessor.hxx>

template<typename T>
sk::util::CloningProcessor<T>::
CloningProcessor(sk::util::Collection<T>& depot)
  : _depot(depot)
{
}

template<typename T>
sk::util::CloningProcessor<T>::
~CloningProcessor()
{
}

template<typename T>
void
sk::util::CloningProcessor<T>::
process(T& object) const
{
  _depot.add(object.clone());
}

#endif /* _SK_UTIL_CLONINGPROCESSOR_CXX_ */
