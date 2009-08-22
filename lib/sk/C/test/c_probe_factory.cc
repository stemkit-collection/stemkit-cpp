/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/C/test/Probe.h>
#include <sk/C/handle.h>
#include "c_probe_factory_implementation.h"
#include <stdlib.h>

extern "C"
struct sk_c_test_ProbeFactoryHandle* sk_c_test_ProbeFactory_create()
{
  return new sk_c_test_ProbeFactoryHandle(new sk::C::test::ProbeFactory);
}

extern "C"
void sk_c_test_ProbeFactory_destroy(struct sk_c_test_ProbeFactoryHandle* handle)
{
  sk_c_handle::ensure_proper(handle);
  delete handle;
}

extern "C"
int sk_c_test_ProbeFactory_getSize(const struct sk_c_test_ProbeFactoryHandle* handle)
{
  sk_c_handle::ensure_proper(handle);
  return handle->get().getSize();
}

extern "C"
struct sk_c_test_ProbeHandle* sk_c_test_ProbeFactory_makeProbe(struct sk_c_test_ProbeFactoryHandle* handle, const char* name)
{
  sk_c_handle::ensure_proper(handle);
  return handle->get().makeProbe(name).get_c_handle();
}
