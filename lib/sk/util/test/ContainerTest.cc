/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ContainerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ContainerTest);

sk::util::test::ContainerTest::
ContainerTest()
{
}

sk::util::test::ContainerTest::
~ContainerTest()
{
}

void
sk::util::test::ContainerTest::
setUp()
{
}

void
sk::util::test::ContainerTest::
tearDown()
{
}

void
sk::util::test::ContainerTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
