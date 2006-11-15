/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PtyTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::PtyTest);

sk::io::test::PtyTest::
PtyTest()
{
}

sk::io::test::PtyTest::
~PtyTest()
{
}

void
sk::io::test::PtyTest::
setUp()
{
}

void
sk::io::test::PtyTest::
tearDown()
{
}

void
sk::io::test::PtyTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
