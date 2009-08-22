/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "api/Probe.h"
#include "c_probe_factory_implementation.h"
#include <stdlib.h>

extern "C"
struct sk_util_test_ProbeFactoryHandle* sk_util_test_ProbeFactory_create()
{
  return new sk_util_test_ProbeFactoryHandle(new sk::util::test::ProbeFactory);
}

extern "C"
void sk_util_test_ProbeFactory_destroy(struct sk_util_test_ProbeFactoryHandle* handle)
{
  if(handle == 0) {
    abort();
  }
  delete handle;
}

extern "C"
int sk_util_test_ProbeFactory_getSize(const struct sk_util_test_ProbeFactoryHandle* handle)
{
  if(handle == 0) {
    abort();
  }
  return handle->get().getSize();
}

extern "C"
struct sk_util_test_ProbeHandle* sk_util_test_ProbeFactory_makeProbe(struct sk_util_test_ProbeFactoryHandle* handle, const char* name)
{
  if(handle == 0) {
    abort();
  }
  return handle->get().makeProbe(name).get_c_handle();
}
