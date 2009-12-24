/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STANDARDCONTAINER_CXX_
#define _SK_UTIL_STANDARDCONTAINER_CXX_

#include <sk/util/StandardContainer.hxx>

template<typename T, typename Policy, typename Provider>
sk::util::StandardContainer<T, Policy, Provider>::
StandardContainer()
{
}

template<typename T, typename Policy, typename Provider>
sk::util::StandardContainer<T, Policy, Provider>::
~StandardContainer()
{
}

template<typename T, typename Policy, typename Provider>
void
sk::util::StandardContainer<T, Policy, Provider>::
process(T& object)
{
}

#endif /* _SK_UTIL_STANDARDCONTAINER_CXX_ */
