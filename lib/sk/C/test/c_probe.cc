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

struct sk_c_handle* sk_c_test_ProbeHandle_toHandle(struct sk_c_test_ProbeHandle* handle)
{
  return handle;
}

extern "C"
const char* sk_c_test_Probe_inspect(const struct sk_c_test_ProbeHandle* handle, char* buffer, int size)
{
  sk_c_handle::ensure_proper(handle);
  struct Action : public virtual sk::util::Mapper<sk::C::test::Probe, sk::util::String> {
    sk::util::String map(sk::C::test::Probe& probe) const {
      return probe.inspect();
    }
  };
  return sk_c_handle::copy(handle->invoke(Action()), buffer, size);
}

extern "C"
void sk_c_test_Probe_raiseException(const struct sk_c_test_ProbeHandle* handle, const char* message)
{
  sk_c_handle::ensure_proper(handle);
  struct Action : public virtual sk::util::Mapper<sk::C::test::Probe, bool> {
    Action(const char* message) 
      : _message(message) {}

    bool map(sk::C::test::Probe& probe) const {
      probe.raiseException(_message);
      return false;
    }
    const char* _message;
  };
  handle->invoke(Action(message));
}

extern "C"
int sk_c_test_Probe_getInstanceCounter()
{
  return sk::C::test::Probe::getInstanceCouner();
}
