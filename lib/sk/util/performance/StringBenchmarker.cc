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
#include <sk/util/InsufficientMemoryException.h>
#include <sk/rt/Benchmark.h>
#include <memory.h>
#include <stdlib.h>
#include <strings.h>

#include "StringBenchmarker.h"

static const sk::util::String __className("sk::util::performance::StringBenchmarker");

sk::util::performance::StringBenchmarker::
StringBenchmarker()
  : sk::rt::Benchmarker("String benchmarks")
{
}

sk::util::performance::StringBenchmarker::
~StringBenchmarker()
{
}

const sk::util::Class
sk::util::performance::StringBenchmarker::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct StringCreation : public virtual sk::rt::Benchmark {
    void run() {
      for(int counter = 100000; counter; --counter) {
        sk::util::String* s = new sk::util::String("abc");
        delete s;
      }
    }
  };

  struct StandardStringCreation : public virtual sk::rt::Benchmark {
    void run() {
      for(int counter = 100000; counter; --counter) {
        std::string* s = new std::string("abc");
        delete s;
      }
    }
  };
}

namespace {
  void c_string_creation() {
    for(int counter = 100000; counter; --counter) {
      char* s = (char*)malloc(4);
      if(s == 0) {
        throw sk::util::InsufficientMemoryException("plain C string", 4);
      }
      strcpy(s, "abc");
      free(s);
    }
  }
}

void
sk::util::performance::StringBenchmarker::
setUp()
{
  add("100,000 sk::util::String", new StringCreation());
  add("100,000 std::string", new StandardStringCreation());
  add("100,000 char*", c_string_creation);
}
