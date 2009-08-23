/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Mapper.h>
#include <sk/C/test/Probe.h>
#include <sk/C/handle.h>

#include "c_probe_factory_implementation.h"

extern "C"
struct sk_c_test_ProbeFactoryHandle* sk_c_test_ProbeFactory_create()
{
  struct Action : public virtual sk::util::Mapper<bool, sk::C::test::ProbeFactory*> {
    sk::C::test::ProbeFactory* map(bool&) const {
      return new sk::C::test::ProbeFactory;
    }
  };
  return new sk_c_test_ProbeFactoryHandle(Action());
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
  struct Action : public virtual sk::util::Mapper<const sk::C::test::ProbeFactory, int> {
    int map(const sk::C::test::ProbeFactory& factory) const {
      return factory.getSize();
    }
  };
  return handle->invoke(Action());
}

extern "C"
struct sk_c_test_ProbeHandle* sk_c_test_ProbeFactory_makeProbe(struct sk_c_test_ProbeFactoryHandle* handle, const char* name)
{
  sk_c_handle::ensure_proper(handle);
  struct Action : public virtual sk::util::Mapper<sk::C::test::ProbeFactory, sk_c_test_ProbeHandle*> {
    Action(const char* name)
      : _name(name) {}

    sk_c_test_ProbeHandle* map(sk::C::test::ProbeFactory& factory) const {
      return factory.makeProbe(_name).get_c_handle();
    }
    const char* _name;
  };
  return handle->invoke(Action(name));
}
