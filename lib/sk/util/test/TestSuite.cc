
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ObjectTest.h"

int main(int argc,char **argv)
{     
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(sk::util::test::ObjectTest::suite());

  return !runner.run();
}
