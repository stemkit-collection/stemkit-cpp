/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include "c_probe_implementation.h"

extern "C"
const char* sk_util_test_Probe_inspect(const struct sk_util_test_ProbeHandle* handle, char* buffer, int size)
{
  if(handle == 0 || buffer == 0 || size <= 0) {
    abort();
  }
  return handle->get().copy(handle->get().inspect(), buffer, size);

  return buffer;
}
