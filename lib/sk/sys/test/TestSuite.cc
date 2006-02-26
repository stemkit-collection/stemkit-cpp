
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "TrashDisposerTest.h"

int main(int argc,char **argv)
{     
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(sk::sys::test::TrashDisposerTest::suite());

  return !runner.run();
}
