/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_TEST_C_PROBE_FACTORY_H_
#define _SK_C_TEST_C_PROBE_FACTORY_H_

struct sk_c_test_ProbeFactoryHandle;

#include <sk/C/test/c_probe.h>
#include <sk/C/handle.h>

#if defined(__cplusplus)
extern "C" {
#endif


struct sk_c_handle* sk_c_test_ProbeFactoryHandle_toHandle(struct sk_c_test_ProbeFactoryHandle* handle);

struct sk_c_test_ProbeFactoryHandle* sk_c_test_ProbeFactory_create();
void sk_c_test_ProbeFactory_destroy(struct sk_c_test_ProbeFactoryHandle* handle);
int sk_c_test_ProbeFactory_getSize(const struct sk_c_test_ProbeFactoryHandle* handle);
struct sk_c_test_ProbeHandle* sk_c_test_ProbeFactory_makeProbe(struct sk_c_test_ProbeFactoryHandle* handle, const char* name);

#if defined(__cplusplus)
}
#endif

#endif /* _SK_C_TEST_C_PROBE_FACTORY_H_ */
