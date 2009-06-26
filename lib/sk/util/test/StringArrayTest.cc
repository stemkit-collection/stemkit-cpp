/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringArrayTest.h"
#include <sk/util/StringArray.h>
#include <sk/util/Class.h>
#include <sk/util/IndexOutOfBoundsException.h>

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
  sk::util::StringArray strings("aaa");
  CPPUNIT_ASSERT_EQUAL(1, strings.size());

  strings = strings + strings;
  CPPUNIT_ASSERT_EQUAL(2, strings.size());

  strings = strings + strings;
  CPPUNIT_ASSERT_EQUAL(4, strings.size());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(2));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(3));
}

void
sk::util::test::StringArrayTest::
testPopulate()
{
  sk::util::StringArray depot;
  CPPUNIT_ASSERT_EQUAL(0, depot.size());
  CPPUNIT_ASSERT_EQUAL(true, depot.isEmpty());

  depot << "aaa";
  depot << "bbb";

  CPPUNIT_ASSERT_EQUAL(false, depot.isEmpty());
  CPPUNIT_ASSERT_EQUAL(2, depot.size());
  CPPUNIT_ASSERT_EQUAL("sk::util::StringArray[ \"aaa\", \"bbb\" ]", depot.inspect());
}

void
sk::util::test::StringArrayTest::
testPlusOther()
{
  const sk::util::StringArray strings("aaa");
  const sk::util::StringArray result = (strings + "bbb");

  CPPUNIT_ASSERT_EQUAL(2, result.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bbb"), result.get(1));
}

void
sk::util::test::StringArrayTest::
testAddString()
{
  sk::util::StringArray strings("aaa");
  CPPUNIT_ASSERT_EQUAL(1, strings.size());

  strings << "bbb" << "ccc";
  CPPUNIT_ASSERT_EQUAL(3, strings.size());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bbb"), strings.get(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("ccc"), strings.get(2));

  CPPUNIT_ASSERT_THROW(strings.get(3), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::StringArrayTest::
testInspect()
{
  sk::util::StringArray strings;
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[]", strings.inspect());

  strings << "aaa";
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[ \"aaa\" ]", strings.inspect());

  strings << "bbb";
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[ \"aaa\", \"bbb\" ]", strings.inspect());
}

void
sk::util::test::StringArrayTest::
testParseDefault()
{
  CPPUNIT_ASSERT_EQUAL(0, sk::util::StringArray::parse("").size());

  sk::util::StringArray strings = sk::util::StringArray::parse("aaa bbb ccc");
  CPPUNIT_ASSERT_EQUAL(3, strings.size());

  CPPUNIT_ASSERT_EQUAL("aaa", strings.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", strings.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", strings.get(2));
}

void
sk::util::test::StringArrayTest::
testParseWithSeparator()
{
  CPPUNIT_ASSERT_EQUAL(0, sk::util::StringArray::parse("", ":").size());

  sk::util::StringArray strings = sk::util::StringArray::parse("AAA:BBB:CCC::DDD", ":");
  CPPUNIT_ASSERT_EQUAL(5, strings.size());

  CPPUNIT_ASSERT_EQUAL("AAA", strings.get(0));
  CPPUNIT_ASSERT_EQUAL("BBB", strings.get(1));
  CPPUNIT_ASSERT_EQUAL("CCC", strings.get(2));
  CPPUNIT_ASSERT_EQUAL("", strings.get(3));
  CPPUNIT_ASSERT_EQUAL("DDD", strings.get(4));
}

void 
sk::util::test::StringArrayTest::
testJoin()
{
  CPPUNIT_ASSERT_EQUAL("", sk::util::StringArray().join(":"));
  CPPUNIT_ASSERT_EQUAL("", sk::util::StringArray().join("> ", ":"));
  CPPUNIT_ASSERT_EQUAL("", sk::util::StringArray().join(" [", ":", "]"));

  sk::util::StringArray data = sk::util::StringArray::parse("aaa bbb ccc");

  CPPUNIT_ASSERT_EQUAL("aaa:bbb:ccc", data.join(":"));
  CPPUNIT_ASSERT_EQUAL("> aaa:bbb:ccc", data.join("> ", ":"));
  CPPUNIT_ASSERT_EQUAL("(aaa:bbb:ccc)", data.join("(", ":", ")"));
}
