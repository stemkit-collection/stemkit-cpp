/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ConfiguratorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::ConfiguratorTest);

sk::sys::test::ConfiguratorTest::
ConfiguratorTest()
{
}

sk::sys::test::ConfiguratorTest::
~ConfiguratorTest()
{
}

void
sk::sys::test::ConfiguratorTest::
setUp()
{
}

void
sk::sys::test::ConfiguratorTest::
tearDown()
{
}

void
sk::sys::test::ConfiguratorTest::
testSimple()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
