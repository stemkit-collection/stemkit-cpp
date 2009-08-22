/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_
#define _SK_C_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_

#include <sk/C/test/Probe.h>
#include <sk/C/test/c_probe.h>

#include <sk/C/abstract_handle.cxx>

struct sk_c_test_ProbeHandle 
  : public sk::C::abstract_handle<sk::C::test::Probe> 
{
  sk_c_test_ProbeHandle(sk::C::test::Probe& object)
    : sk::C::abstract_handle<sk::C::test::Probe>(object) {}
};

#endif /* _SK_C_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_ */
