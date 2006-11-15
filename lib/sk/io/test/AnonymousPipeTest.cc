/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AnonymousPipeTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::AnonymousPipeTest);

sk::io::test::AnonymousPipeTest::
AnonymousPipeTest()
{
}

sk::io::test::AnonymousPipeTest::
~AnonymousPipeTest()
{
}

void
sk::io::test::AnonymousPipeTest::
setUp()
{
}

void
sk::io::test::AnonymousPipeTest::
tearDown()
{
}

void
sk::io::test::AnonymousPipeTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
