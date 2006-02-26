/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ClassTest.h"

sk::util::test::ClassTest::
ClassTest()
{
}

sk::util::test::ClassTest::
~ClassTest()
{
}

void
sk::util::test::ClassTest::
setUp()
{
}

void
sk::util::test::ClassTest::
tearDown()
{
}

void
sk::util::test::ClassTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
