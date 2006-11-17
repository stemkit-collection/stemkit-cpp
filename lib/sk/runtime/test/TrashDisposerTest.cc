/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "TrashDisposerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::TrashDisposerTest);

sk::sys::test::TrashDisposerTest::
TrashDisposerTest()
{
}

sk::sys::test::TrashDisposerTest::
~TrashDisposerTest()
{
}

void
sk::sys::test::TrashDisposerTest::
setUp()
{
}

void
sk::sys::test::TrashDisposerTest::
tearDown()
{
}

void
sk::sys::test::TrashDisposerTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
