/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/rt/Benchmark.h>

static const sk::util::String __className("sk::rt::Benchmark");

const sk::util::Class
sk::rt::Benchmark::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::Benchmark::
setup()
{
}

void
sk::rt::Benchmark::
reset()
{
}
