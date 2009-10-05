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
#include <sk/C/test/c_probe_factory.h>
#include <string.h>

const char* test_probe_factory(char* error_buffer, int error_buffer_size) 
{
  struct sk_c_test_ProbeFactoryHandle* factory = sk_c_test_ProbeFactory_create();
  if(factory == 0) {
    return "Cannot create factory";
  }
  if(sk_c_handle_isError(sk_c_test_ProbeFactoryHandle_toHandle(factory))) {
    return sk_c_handle_errorMessage(sk_c_test_ProbeFactoryHandle_toHandle(factory), error_buffer, error_buffer_size);
  }

  if(sk_c_test_ProbeFactory_getSize(factory) != 0) {
    return "Initial factory size not 0";
  }

  char buffer[80];
  if(strcmp(sk_c_test_Probe_inspect(sk_c_test_ProbeFactory_makeProbe(factory, "AAA"), buffer, sizeof(buffer)), "sk::C::test::Probe=\"AAA\"") != 0) {
    return "Probe not AAA";
  }

  if(strcmp(sk_c_test_Probe_inspect(sk_c_test_ProbeFactory_makeProbe(factory, "BBB"), buffer, sizeof(buffer)), "sk::C::test::Probe=\"BBB\"") != 0) {
    return "Probe not BBB";
  }

  if(sk_c_test_ProbeFactory_getSize(factory) != 2) {
    return "Resulting factory size not 2";
  }

  if(sk_c_test_Probe_getInstanceCounter() != 2) {
    return "Final probe instance counter not 2";
  }

  struct sk_c_test_ProbeHandle* probe = sk_c_test_ProbeFactory_makeProbe(factory, "UUU");
  sk_c_test_Probe_raiseException(probe, "abc");
  if(!sk_c_handle_isError(sk_c_test_ProbeHandle_toHandle(probe))) {
    return "No expected error";
  }

  sk_c_handle_errorMessage(sk_c_test_ProbeHandle_toHandle(probe), error_buffer, error_buffer_size);
  if(strcmp("ERROR: UUU => abc", error_buffer) != 0) {
    strcat(error_buffer, " - ");
    strcat(error_buffer, "Error message mismatch");

    return error_buffer;
  }

  sk_c_handle_errorType(sk_c_test_ProbeHandle_toHandle(probe), error_buffer, error_buffer_size);
  if(strcmp("sk::util::Exception", error_buffer) != 0) {
    strcat(error_buffer, " - ");
    strcat(error_buffer, "Error type mismatch");

    return error_buffer;
  }

  sk_c_test_ProbeFactory_destroy(factory);
  return "OK";
}
