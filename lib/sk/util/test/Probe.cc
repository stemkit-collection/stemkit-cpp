/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>

#include "Probe.h"

int sk::util::test::Probe::_counter = 0;

sk::util::test::Probe::
Probe(const sk::util::String& name)
  : _name(name)
{
  _counter++;
}

sk::util::test::Probe::
~Probe()
{
  _counter--;
}

const sk::util::Class
sk::util::test::Probe::
getClass() const
{
  return sk::util::Class("sk::util::test::Probe");
}

const sk::util::String
sk::util::test::Probe::
getName() const
{ 
  return _name;
}

void 
sk::util::test::Probe::
resetCounter()
{
  _counter = 0;
}

int
sk::util::test::Probe::
getCounter()
{
  return _counter;
}
