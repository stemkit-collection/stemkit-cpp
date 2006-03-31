
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "TrashDisposerTest.h"

#include <sk/cppunit/TestRunner.h>

int main(int argc, char **argv)
{     
  sk::cppunit::TestRunner runner;

  runner.addTest(sk::sys::test::TrashDisposerTest::suite());

  return !runner.run();
}
