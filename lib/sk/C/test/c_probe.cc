/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "c_probe_implementation.h"

extern "C"
const char* sk_c_test_Probe_inspect(const struct sk_c_test_ProbeHandle* handle, char* buffer, int size)
{
  if(handle == 0 || buffer == 0 || size <= 0) {
    abort();
  }
  return sk::C::handle::copy(handle->get().inspect(), buffer, size);
}

extern "C"
int sk_c_test_Probe_getInstanceCounter()
{
  return sk::C::test::Probe::getInstanceCouner();
}
