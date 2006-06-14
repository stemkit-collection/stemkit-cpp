/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AbstractListTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::AbstractListTest);

sk::util::test::AbstractListTest::
AbstractListTest()
{
}

sk::util::test::AbstractListTest::
~AbstractListTest()
{
}

void
sk::util::test::AbstractListTest::
setUp()
{
}

void
sk::util::test::AbstractListTest::
tearDown()
{
}

void
sk::util::test::AbstractListTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
