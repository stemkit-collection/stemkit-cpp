/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileDescriptorOutputStreamTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileDescriptorOutputStreamTest);

sk::io::test::FileDescriptorOutputStreamTest::
FileDescriptorOutputStreamTest()
{
}

sk::io::test::FileDescriptorOutputStreamTest::
~FileDescriptorOutputStreamTest()
{
}

void
sk::io::test::FileDescriptorOutputStreamTest::
setUp()
{
}

void
sk::io::test::FileDescriptorOutputStreamTest::
tearDown()
{
}

void
sk::io::test::FileDescriptorOutputStreamTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
