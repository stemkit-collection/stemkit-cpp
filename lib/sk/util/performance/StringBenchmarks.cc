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

#include "StringBenchmarks.h"

static const sk::util::String __className("sk::util::performance::StringBenchmarks");

sk::util::performance::StringBenchmarks::
StringBenchmarks()
  : sk::rt::Benchmark("String benchmarks")
{
}

sk::util::performance::StringBenchmarks::
~StringBenchmarks()
{
}

const sk::util::Class
sk::util::performance::StringBenchmarks::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct StringCreation : public virtual sk::rt::Runnable {
    void run() {
      for(int counter = 100000; counter; --counter) {
        sk::util::String* s = new sk::util::String("abc");
      }
    }
  };
}

void 
sk::util::performance::StringBenchmarks::
setUp()
{
  add("100,000 sk::util::String", new StringCreation());
}
