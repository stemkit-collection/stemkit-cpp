/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_ALIASINGPROCESSOR_CXX_
#define _SK_UTIL_ALIASINGPROCESSOR_CXX_

#include <sk/util/AliasingProcessor.hxx>

template<typename T>
sk::util::AliasingProcessor<T>::
AliasingProcessor(sk::util::Collection<T>& depot)
  : _depot(depot)
{
}

template<typename T>
sk::util::AliasingProcessor<T>::
~AliasingProcessor()
{
}

template<typename T>
void
sk::util::AliasingProcessor<T>::
process(T& object) const
{
  _depot.add(object);
}

#endif /* _SK_UTIL_ALIASINGPROCESSOR_CXX_ */
