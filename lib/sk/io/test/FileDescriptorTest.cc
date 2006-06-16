/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileDescriptorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::FileDescriptorTest);

sk::io::test::FileDescriptorTest::
FileDescriptorTest()
{
}

sk::io::test::FileDescriptorTest::
~FileDescriptorTest()
{
}

void
sk::io::test::FileDescriptorTest::
setUp()
{
}

void
sk::io::test::FileDescriptorTest::
tearDown()
{
}

void
sk::io::test::FileDescriptorTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
