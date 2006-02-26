/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ObjectTest.h"

sk::util::test::ObjectTest::
ObjectTest()
{
}

sk::util::test::ObjectTest::
~ObjectTest()
{
}

void
sk::util::test::ObjectTest::
setUp()
{
}

void
sk::util::test::ObjectTest::
tearDown()
{
}

void
sk::util::test::ObjectTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
