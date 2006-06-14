/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "IOExceptionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::IOExceptionTest);

sk::io::test::IOExceptionTest::
IOExceptionTest()
{
}

sk::io::test::IOExceptionTest::
~IOExceptionTest()
{
}

void
sk::io::test::IOExceptionTest::
setUp()
{
}

void
sk::io::test::IOExceptionTest::
tearDown()
{
}

void
sk::io::test::IOExceptionTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
