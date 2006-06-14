/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "DataOutputStreamTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::DataOutputStreamTest);

sk::io::test::DataOutputStreamTest::
DataOutputStreamTest()
{
}

sk::io::test::DataOutputStreamTest::
~DataOutputStreamTest()
{
}

void
sk::io::test::DataOutputStreamTest::
setUp()
{
}

void
sk::io::test::DataOutputStreamTest::
tearDown()
{
}

void
sk::io::test::DataOutputStreamTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
