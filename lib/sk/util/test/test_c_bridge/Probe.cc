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
#include <sk/util/c_handle_provider.cxx>

#include "api/Probe.h"
#include "c_probe_implementation.h"

static const sk::util::String __className("sk::util::test::Probe");

sk::util::test::Probe::
Probe(const sk::util::String& name)
  : _name(name), c_handle_provider<Probe, sk_util_test_ProbeHandle>(*this)
{
}

sk::util::test::Probe::
~Probe()
{
}

const sk::util::Class
sk::util::test::Probe::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::util::test::Probe::
inspect() const 
{
  return getClass().getName() + "=" + _name.inspect();
}
