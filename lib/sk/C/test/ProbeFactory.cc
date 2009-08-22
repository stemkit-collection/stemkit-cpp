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

#include "api/ProbeFactory.h"
#include "api/Probe.h"

static const char* __className("sk::util::test::ProbeFactory");

sk::util::test::ProbeFactory::
ProbeFactory()
{
}

sk::util::test::ProbeFactory::
~ProbeFactory()
{
}

const sk::util::Class
sk::util::test::ProbeFactory::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::util::test::ProbeFactory::
getSize() const
{
  return _probes.size();
}

sk::util::test::Probe&
sk::util::test::ProbeFactory::
makeProbe(const sk::util::String& name) 
{
  _probes.add(new sk::util::test::Probe(name));
  return _probes.get(_probes.size() - 1);
}
