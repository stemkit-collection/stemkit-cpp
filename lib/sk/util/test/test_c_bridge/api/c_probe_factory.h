/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_C_PROBE_FACTORY_H_
#define _SK_UTIL_TEST_C_PROBE_FACTORY_H_

struct sk_util_test_ProbeFactoryHandle;
#include <api/c_probe.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct sk_util_test_ProbeFactoryHandle* sk_util_test_ProbeFactory_create();
void sk_util_test_ProbeFactory_destroy(struct sk_util_test_ProbeFactoryHandle* handle);
int sk_util_test_ProbeFactory_getSize(const struct sk_util_test_ProbeFactoryHandle* handle);
struct sk_util_test_ProbeHandle* sk_util_test_ProbeFactory_makeProbe(struct sk_util_test_ProbeFactoryHandle* handle, const char* name);

#if defined(__cplusplus)
}
#endif

#endif /* _SK_UTIL_TEST_C_PROBE_FACTORY_H_ */
