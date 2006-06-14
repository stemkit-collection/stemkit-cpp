/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "EOFExceptionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::EOFExceptionTest);

sk::io::test::EOFExceptionTest::
EOFExceptionTest()
{
}

sk::io::test::EOFExceptionTest::
~EOFExceptionTest()
{
}

void
sk::io::test::EOFExceptionTest::
setUp()
{
}

void
sk::io::test::EOFExceptionTest::
tearDown()
{
}

void
sk::io::test::EOFExceptionTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
