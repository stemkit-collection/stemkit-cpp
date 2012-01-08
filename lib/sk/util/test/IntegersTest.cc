/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "IntegersTest.h"
#include <sk/util/Integers.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::IntegersTest);

sk::util::test::IntegersTest::
IntegersTest()
{
}

sk::util::test::IntegersTest::
~IntegersTest()
{
}

void
sk::util::test::IntegersTest::
setUp()
{
}

void
sk::util::test::IntegersTest::
tearDown()
{
}

void
sk::util::test::IntegersTest::
testBasics()
{
  sk::util::Integers array;
  array << 1 << 2 << 3;
  CPPUNIT_ASSERT_EQUAL("sk::util::Integers[ 1, 2, 3 ]", array.inspect());
  CPPUNIT_ASSERT_EQUAL("123", array.toString());

  CPPUNIT_ASSERT(array.contains(1) == true);
  CPPUNIT_ASSERT(array.contains(2) == true);
  CPPUNIT_ASSERT(array.contains(3) == true);
  CPPUNIT_ASSERT(array.contains(4) == false);
}
