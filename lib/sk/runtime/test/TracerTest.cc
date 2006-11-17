/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "TracerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::TracerTest);

sk::sys::test::TracerTest::
TracerTest()
{
}

sk::sys::test::TracerTest::
~TracerTest()
{
}

void
sk::sys::test::TracerTest::
setUp()
{
}

void
sk::sys::test::TracerTest::
tearDown()
{
}

void
sk::sys::test::TracerTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
