/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ProcessTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::ProcessTest);

sk::io::test::ProcessTest::
ProcessTest()
{
}

sk::io::test::ProcessTest::
~ProcessTest()
{
}

void
sk::io::test::ProcessTest::
setUp()
{
}

void
sk::io::test::ProcessTest::
tearDown()
{
}

void
sk::io::test::ProcessTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
