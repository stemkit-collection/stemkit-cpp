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
#include <sk/util/ArrayList.cxx>

#include <sk/C/test/ProbeFactory.h>
#include <sk/C/test/Probe.h>

static const char* __className("sk::C::test::ProbeFactory");

sk::C::test::ProbeFactory::
ProbeFactory()
{
}

sk::C::test::ProbeFactory::
~ProbeFactory()
{
}

const sk::util::Class
sk::C::test::ProbeFactory::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::C::test::ProbeFactory::
getSize() const
{
  return _probes.size();
}

sk::C::test::Probe&
sk::C::test::ProbeFactory::
makeProbe(const sk::util::String& name) 
{
  _probes.add(new sk::C::test::Probe(name));
  return _probes.get(_probes.size() - 1);
}
