/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileInputStreamTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileInputStreamTest);

sk::io::test::FileInputStreamTest::
FileInputStreamTest()
{
}

sk::io::test::FileInputStreamTest::
~FileInputStreamTest()
{
}

void
sk::io::test::FileInputStreamTest::
setUp()
{
}

void
sk::io::test::FileInputStreamTest::
tearDown()
{
}

void
sk::io::test::FileInputStreamTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
