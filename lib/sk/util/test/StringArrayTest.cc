/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringArrayTest.h"
#include <sk/util/StringArray.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::StringArrayTest);

sk::util::test::StringArrayTest::
StringArrayTest()
{
}

sk::util::test::StringArrayTest::
~StringArrayTest()
{
}

void
sk::util::test::StringArrayTest::
setUp()
{
}

void
sk::util::test::StringArrayTest::
tearDown()
{
}

void
sk::util::test::StringArrayTest::
testEmpty()
{
  sk::util::StringArray strings;

  CPPUNIT_ASSERT_EQUAL(0, strings.size());
}

void
sk::util::test::StringArrayTest::
testOne()
{
  sk::util::StringArray strings("abcd");

  CPPUNIT_ASSERT_EQUAL(1, strings.size());
}

void
sk::util::test::StringArrayTest::
testPlusString()
{
  const sk::util::StringArray strings("aaa");
  const sk::util::StringArray result = (strings + "bbb");

  CPPUNIT_ASSERT_EQUAL(2, result.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bbb"), result.get(1));
}
