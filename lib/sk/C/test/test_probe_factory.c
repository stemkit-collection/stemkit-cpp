/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "test_probe_factory.h"
#include <api/c_probe_factory.h>

const char* test_probe_factory() 
{
  struct sk_util_test_ProbeFactoryHandle* factory = sk_util_test_ProbeFactory_create();
  if(factory == 0) {
    return "Cannot create factory";
  }

  if(sk_util_test_ProbeFactory_getSize(factory) != 0) {
    return "Initial factory size not 0";
  }

  char buffer[80];
  if(strcmp(sk_util_test_Probe_inspect(sk_util_test_ProbeFactory_makeProbe(factory, "AAA"), buffer, sizeof(buffer)), "sk::util::test::Probe=\"AAA\"") != 0) {
    return "Probe not AAA";
  }

  if(strcmp(sk_util_test_Probe_inspect(sk_util_test_ProbeFactory_makeProbe(factory, "BBB"), buffer, sizeof(buffer)), "sk::util::test::Probe=\"BBB\"") != 0) {
    return "Probe not BBB";
  }

  if(sk_util_test_ProbeFactory_getSize(factory) != 2) {
    return "Resulting factory size not 2";
  }

  if(sk_util_test_Probe_getInstanceCounter() != 2) {
    return "Final probe instance counter not 2";
  }

  sk_util_test_ProbeFactory_destroy(factory);
  return "OK";
}
