/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_H_
#define _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_H_

struct sk_util_test_ProbeHandle;

#if defined(__cplusplus)
extern "C" {
#endif

const char* sk_util_test_Probe_inspect(const struct sk_util_test_ProbeHandle* handle, char* buffer, int size);

#if defined(__cplusplus)
}
#endif

#endif /* _SK_UTIL_TEST_TEST_C_BRIDGE_C_PROBE_H_ */
