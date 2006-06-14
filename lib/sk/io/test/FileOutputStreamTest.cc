/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileOutputStreamTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileOutputStreamTest);

sk::io::test::FileOutputStreamTest::
FileOutputStreamTest()
{
}

sk::io::test::FileOutputStreamTest::
~FileOutputStreamTest()
{
}

void
sk::io::test::FileOutputStreamTest::
setUp()
{
}

void
sk::io::test::FileOutputStreamTest::
tearDown()
{
}

void
sk::io::test::FileOutputStreamTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
