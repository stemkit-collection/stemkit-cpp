/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileDescriptorInputStreamTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileDescriptorInputStreamTest);

sk::io::test::FileDescriptorInputStreamTest::
FileDescriptorInputStreamTest()
{
}

sk::io::test::FileDescriptorInputStreamTest::
~FileDescriptorInputStreamTest()
{
}

void
sk::io::test::FileDescriptorInputStreamTest::
setUp()
{
}

void
sk::io::test::FileDescriptorInputStreamTest::
tearDown()
{
}

void
sk::io::test::FileDescriptorInputStreamTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
