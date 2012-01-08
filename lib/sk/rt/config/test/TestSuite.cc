/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>

#include <iostream>

#include <sk/rt/Scope.h>

int main(int argc, char **argv)
{
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  sk::cppunit::TestRunner runner;

  // sk::rt::Scope::controller().getAggregator().getConfig().setLogLevel(sk::rt::logger::Level::DEBUG);

  if(argc == 2) {
    sk::cppunit::SourcePath::setBase(argv[1]);
  }
  runner.addTest(registry.makeTest());
  return !runner.run();
}
