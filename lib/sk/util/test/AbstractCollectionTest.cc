/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AbstractCollectionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::AbstractCollectionTest);

sk::util::test::AbstractCollectionTest::
AbstractCollectionTest()
{
}

sk::util::test::AbstractCollectionTest::
~AbstractCollectionTest()
{
}

void
sk::util::test::AbstractCollectionTest::
setUp()
{
}

void
sk::util::test::AbstractCollectionTest::
tearDown()
{
}

void
sk::util::test::AbstractCollectionTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
