/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>
#include <sk/util/test/Probe.cxx>
#include <sk/util/String.h>

#include <iostream>

int main(int argc, char **argv)
{
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  sk::cppunit::TestRunner runner;

  if(argc == 2) {
    sk::cppunit::SourcePath::setBase(argv[1]);
  }
  runner.addTest(registry.makeTest());
  return !runner.run();
}

// Forcing template instantiation for the types used in other
// test classes.

template class sk::util::test::Probe<sk::util::String>;

