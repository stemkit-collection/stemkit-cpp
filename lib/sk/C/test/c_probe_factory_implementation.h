/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_
#define _SK_UTIL_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_

#include "api/ProbeFactory.h"
#include "api/c_probe_factory.h"

#include <sk/C/abstract_handle.cxx>

struct sk_util_test_ProbeFactoryHandle 
  : public sk::C::abstract_handle<sk::util::test::ProbeFactory> 
{
  sk_util_test_ProbeFactoryHandle(sk::util::test::ProbeFactory* object)
    : sk::C::abstract_handle<sk::util::test::ProbeFactory>(object) {}
};

#endif /* _SK_UTIL_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_ */
