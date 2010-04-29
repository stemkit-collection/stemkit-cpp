/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/rt/Benchmarker.h>
#include "LockBenchmarker.h"

int main(int /*argc*/, const char* /*argv*/[])
{
  sk::rt::Benchmarker benchmark("stemkit-cpp sk.rt benchmarks");

  benchmark.add(new sk::util::performance::LockBenchmarker());

  benchmark.init();
  benchmark.start();

  benchmark.report(0, std::cout);

  return 0;
}
