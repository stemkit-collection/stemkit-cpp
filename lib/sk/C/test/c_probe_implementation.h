/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_
#define _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_

#include "api/Probe.h"
#include "api/c_probe.h"

#include <sk/util/abstract_c_handle.cxx>

struct sk_util_test_ProbeHandle 
  : public sk::util::abstract_c_handle<sk::util::test::Probe> 
{
  sk_util_test_ProbeHandle(sk::util::test::Probe& object)
    : sk::util::abstract_c_handle<sk::util::test::Probe>(object) {}
};

#endif /* _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_IMPLEMENTATION_H_ */
