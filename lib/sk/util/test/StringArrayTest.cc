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
#include <sk/util/NoSuchElementException.h>

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

void
sk::util::test::StringArrayTest::
testLastFirst()
{
  CPPUNIT_ASSERT_THROW(sk::util::StringArray().first(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(sk::util::StringArray().last(), sk::util::NoSuchElementException);

  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::StringArray::parse("aaa bbb ccc").first());
  CPPUNIT_ASSERT_EQUAL("ccc", sk::util::StringArray::parse("aaa bbb ccc").last());

  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::StringArray::parse("aaa").first());
  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::StringArray::parse("aaa").last());
}

void 
sk::util::test::StringArrayTest::
testPopShift()
{
  sk::util::StringArray array = sk::util::StringArray::parse("aaa bbb ccc");

  CPPUNIT_ASSERT_EQUAL("aaa", array.shift());
  CPPUNIT_ASSERT_EQUAL(2, array.size());

  CPPUNIT_ASSERT_EQUAL("ccc", array.pop());
  CPPUNIT_ASSERT_EQUAL(1, array.size());

  CPPUNIT_ASSERT_EQUAL("bbb", array.shift());
  CPPUNIT_ASSERT_EQUAL(0, array.size());

  CPPUNIT_ASSERT_THROW(array.pop(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(array.shift(), sk::util::NoSuchElementException);
}

void
sk::util::test::StringArrayTest::
testSlice()
{
  sk::util::StringArray data = sk::util::StringArray::parse("aaa bbb ccc");
  CPPUNIT_ASSERT_EQUAL(0, data.slice(0).size());

  sk::util::StringArray s1 = data.slice(1);
  CPPUNIT_ASSERT_EQUAL(1, s1.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s1.get(0));

  sk::util::StringArray s2 = data.slice(2);
  CPPUNIT_ASSERT_EQUAL(2, s2.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s2.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", s2.get(1));

  sk::util::StringArray s3 = data.slice(3);
  CPPUNIT_ASSERT_EQUAL(3, s3.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s3.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", s3.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", s3.get(2));

  CPPUNIT_ASSERT_THROW(data.slice(-1), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(data.slice(4), sk::util::NoSuchElementException);
}
