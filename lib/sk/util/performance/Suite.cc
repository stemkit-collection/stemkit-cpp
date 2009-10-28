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
#include "StringBenchmarker.h"

int main(int argc, const char* argv[])
{
  sk::rt::Benchmarker benchmark("stemkit-cpp util benchmarks");
  sk::util::performance::StringBenchmarker stringBenchmark;

  benchmark.add(stringBenchmark);
  benchmark.add(new sk::util::performance::StringBenchmarker());

  benchmark.init();
  for(int counter=25; counter; --counter) {
    benchmark.start();
  }
  benchmark.report(0, std::cout);

  return 0;
}