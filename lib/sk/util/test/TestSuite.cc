
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ClassTest.h"
#include "ObjectTest.h"
#include "StringTest.h"
#include "IntegerTest.h"

#include <sk/util/CppunitCustomOutputter.h>
 
int main(int argc,char **argv)
{     
  CppUnit::TextUi::TestRunner runner;
  runner.setOutputter(new sk::util::CppunitCustomOutputter(runner));

  runner.addTest(sk::util::test::ClassTest::suite());
  runner.addTest(sk::util::test::ObjectTest::suite());
  runner.addTest(sk::util::test::StringTest::suite());
  runner.addTest(sk::util::test::IntegerTest::suite());

  return !runner.run();
}
