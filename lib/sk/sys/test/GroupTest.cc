/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "GroupTest.h"
#include <sk/sys/Group.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::GroupTest);

sk::sys::test::GroupTest::
GroupTest()
{
}

sk::sys::test::GroupTest::
~GroupTest()
{
}

void
sk::sys::test::GroupTest::
setUp()
{
}

void
sk::sys::test::GroupTest::
tearDown()
{
}

void
sk::sys::test::GroupTest::
testFind()
{
  sk::sys::Group group = sk::sys::Group::find("bin");
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bin"), group.getName());
}
