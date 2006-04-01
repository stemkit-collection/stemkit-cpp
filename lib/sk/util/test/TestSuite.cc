/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ClassTest.h"
#include "ObjectTest.h"
#include "StringTest.h"
#include "IntegerTest.h"

#include <sk/cppunit/TestRunner.h>
 
int main(int argc, char **argv)
{     
  sk::cppunit::TestRunner runner;

  runner.addTest(sk::util::test::ObjectTest::suite());
  runner.addTest(sk::util::test::ClassTest::suite());
  runner.addTest(sk::util::test::StringTest::suite());
  runner.addTest(sk::util::test::IntegerTest::suite());

  return !runner.run();
}
