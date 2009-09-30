/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_
#define _SK_C_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_

#include <sk/C/test/ProbeFactory.h>
#include <sk/C/test/c_probe_factory.h>

#include <sk/C/abstract_handle.cxx>

struct sk_c_test_ProbeFactoryHandle 
  : public sk::C::abstract_handle<sk::C::test::ProbeFactory> 
{
  sk_c_test_ProbeFactoryHandle(sk::C::test::ProbeFactory& object)
    : sk::C::abstract_handle<sk::C::test::ProbeFactory>(object) {}

  sk_c_test_ProbeFactoryHandle(const sk::util::Mapper<bool, sk::C::test::ProbeFactory*>& mapper)
    : sk::C::abstract_handle<sk::C::test::ProbeFactory>(mapper) {}
};

#endif /* _SK_C_TEST_C_PROBE_FACTORY_IMPLEMENTATION_H_ */
