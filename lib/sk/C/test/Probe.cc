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
#include <sk/util/Strings.h>
#include <sk/C/handle_provider.cxx>

#include <sk/C/test/Probe.h>
#include "c_probe_implementation.h"

template class sk::C::handle_provider<sk::C::test::Probe, sk_c_test_ProbeHandle>;

static const sk::util::String __className("sk::C::test::Probe");
int sk::C::test::Probe::__instanceCounter = 0;

sk::C::test::Probe::
Probe(const sk::util::String& name)
  : _name(name), sk::C::handle_provider<Probe, sk_c_test_ProbeHandle>(*this)
{
  ++__instanceCounter;
}

sk::C::test::Probe::
~Probe()
{
  --__instanceCounter;
}

const sk::util::Class
sk::C::test::Probe::
getClass() const
{
  return sk::util::Class(__className);
}


void 
sk::C::test::Probe::
raiseException(const sk::util::String& message) const
{
  throw sk::util::Exception(_name + " => " + message);
}

const sk::util::String
sk::C::test::Probe::
inspect() const 
{
  return getClass().getName() + "=" + _name.inspect();
}

int 
sk::C::test::Probe::
getInstanceCouner() 
{
  return __instanceCounter;
}

void
sk::C::test::Probe::
resetInstanceCouner()
{
  __instanceCounter = 0;
}
