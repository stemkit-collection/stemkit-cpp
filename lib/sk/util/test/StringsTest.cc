/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringsTest.h"
#include <sk/util/Strings.h>
#include <sk/util/Class.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/mapper/Upcasing.h>
#include <sk/util/mapper/Downcasing.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::StringsTest);

sk::util::test::StringsTest::
StringsTest()
{
}

sk::util::test::StringsTest::
~StringsTest()
{
}

void
sk::util::test::StringsTest::
setUp()
{
}

void
sk::util::test::StringsTest::
tearDown()
{
}

void
sk::util::test::StringsTest::
testEmpty()
{
  sk::util::Strings strings;

  CPPUNIT_ASSERT_EQUAL(0, strings.size());
}

void
sk::util::test::StringsTest::
testOne()
{
  sk::util::Strings strings("abcd");

  CPPUNIT_ASSERT_EQUAL(1, strings.size());
}

void
sk::util::test::StringsTest::
testPlusString()
{
  sk::util::Strings strings("aaa");
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
sk::util::test::StringsTest::
testPopulate()
{
  sk::util::Strings depot;
  CPPUNIT_ASSERT_EQUAL(0, depot.size());
  CPPUNIT_ASSERT_EQUAL(true, depot.isEmpty());

  depot << "aaa";
  depot << "bbb";

  CPPUNIT_ASSERT_EQUAL(false, depot.isEmpty());
  CPPUNIT_ASSERT_EQUAL(2, depot.size());
  CPPUNIT_ASSERT_EQUAL("sk::util::Strings[ \"aaa\", \"bbb\" ]", depot.inspect());
}

void
sk::util::test::StringsTest::
testPlusOther()
{
  const sk::util::Strings strings("aaa");
  const sk::util::Strings result = (strings + "bbb");

  CPPUNIT_ASSERT_EQUAL(2, result.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bbb"), result.get(1));
}

void
sk::util::test::StringsTest::
testAddString()
{
  sk::util::Strings strings("aaa");
  CPPUNIT_ASSERT_EQUAL(1, strings.size());

  strings << "bbb" << "ccc";
  CPPUNIT_ASSERT_EQUAL(3, strings.size());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("aaa"), strings.get(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("bbb"), strings.get(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("ccc"), strings.get(2));

  CPPUNIT_ASSERT(strings.contains("aaa") == true);
  CPPUNIT_ASSERT(strings.contains("bbb") == true);
  CPPUNIT_ASSERT(strings.contains("ccc") == true);
  CPPUNIT_ASSERT(strings.contains("ddd") == false);

  CPPUNIT_ASSERT_THROW(strings.get(3), sk::util::IndexOutOfBoundsException);
}

void
sk::util::test::StringsTest::
testInspect()
{
  sk::util::Strings strings;
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[]", strings.inspect());

  strings << "aaa";
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[ \"aaa\" ]", strings.inspect());

  strings << "bbb";
  CPPUNIT_ASSERT_EQUAL(strings.getClass().getName() + "[ \"aaa\", \"bbb\" ]", strings.inspect());
}

void
sk::util::test::StringsTest::
testParseDefault()
{
  CPPUNIT_ASSERT_EQUAL(0, sk::util::String("").split().size());

  sk::util::Strings strings = sk::util::String("aaa bbb ccc").split();
  CPPUNIT_ASSERT_EQUAL(3, strings.size());

  CPPUNIT_ASSERT_EQUAL("aaa", strings.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", strings.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", strings.get(2));
}

void
sk::util::test::StringsTest::
testParseWithSeparator()
{
  CPPUNIT_ASSERT_EQUAL(0, sk::util::String("").split(":").size());

  sk::util::Strings strings = sk::util::String("AAA:BBB:CCC::DDD").split(":");
  CPPUNIT_ASSERT_EQUAL(5, strings.size());

  CPPUNIT_ASSERT_EQUAL("AAA", strings.get(0));
  CPPUNIT_ASSERT_EQUAL("BBB", strings.get(1));
  CPPUNIT_ASSERT_EQUAL("CCC", strings.get(2));
  CPPUNIT_ASSERT_EQUAL("", strings.get(3));
  CPPUNIT_ASSERT_EQUAL("DDD", strings.get(4));
}

void
sk::util::test::StringsTest::
testJoin()
{
  CPPUNIT_ASSERT_EQUAL("", sk::util::Strings().join(":"));
  CPPUNIT_ASSERT_EQUAL("", sk::util::Strings().join("> ", ":"));
  CPPUNIT_ASSERT_EQUAL("", sk::util::Strings().join(" [", ":", "]"));

  sk::util::Strings data = sk::util::String("aaa bbb ccc").split();

  CPPUNIT_ASSERT_EQUAL("aaa:bbb:ccc", data.join(":"));
  CPPUNIT_ASSERT_EQUAL("> aaa:bbb:ccc", data.join("> ", ":"));
  CPPUNIT_ASSERT_EQUAL("(aaa:bbb:ccc)", data.join("(", ":", ")"));
}

void
sk::util::test::StringsTest::
testLastFirst()
{
  CPPUNIT_ASSERT_THROW(sk::util::Strings().first(), sk::util::NoSuchElementException);
  CPPUNIT_ASSERT_THROW(sk::util::Strings().last(), sk::util::NoSuchElementException);

  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::String("aaa bbb ccc").split().first());
  CPPUNIT_ASSERT_EQUAL("ccc", sk::util::String("aaa bbb ccc").split().last());

  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::String("aaa").split().first());
  CPPUNIT_ASSERT_EQUAL("aaa", sk::util::String("aaa").split().last());
}

void
sk::util::test::StringsTest::
testPopShift()
{
  sk::util::Strings array = sk::util::String("aaa bbb ccc").split();

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
sk::util::test::StringsTest::
testSlice()
{
  sk::util::Strings data = sk::util::String("aaa bbb ccc").split();
  CPPUNIT_ASSERT_EQUAL(3, data.size());
  CPPUNIT_ASSERT_EQUAL(0, data.slice(0).size());

  sk::util::Strings s1 = data.slice(1);
  CPPUNIT_ASSERT_EQUAL(1, s1.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s1.get(0));

  sk::util::Strings s2 = data.slice(2);
  CPPUNIT_ASSERT_EQUAL(2, s2.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s2.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", s2.get(1));

  sk::util::Strings s3 = data.slice(3);
  CPPUNIT_ASSERT_EQUAL(3, s3.size());
  CPPUNIT_ASSERT_EQUAL("aaa", s3.get(0));
  CPPUNIT_ASSERT_EQUAL("bbb", s3.get(1));
  CPPUNIT_ASSERT_EQUAL("ccc", s3.get(2));

  CPPUNIT_ASSERT_EQUAL(3, data.slice(-1).size());
  CPPUNIT_ASSERT_EQUAL(0, data.slice(3, 4).size());
}

void
sk::util::test::StringsTest::
testMap()
{
  sk::util::Strings data = sk::util::String("aaa BBB ccc").split();
  CPPUNIT_ASSERT_EQUAL("AAA - BBB - CCC", data.map(sk::util::mapper::Upcasing()).join(" - "));
  CPPUNIT_ASSERT_EQUAL("aaa/bbb/ccc", data.map(sk::util::mapper::Downcasing()).join("/"));
}

void
sk::util::test::StringsTest::
testCopy()
{
  const sk::util::Strings data = sk::util::String("a b c d").split();
  CPPUNIT_ASSERT_EQUAL(4, data.size());

  sk::util::Strings other = data;
  CPPUNIT_ASSERT_EQUAL(4, other.size());
  CPPUNIT_ASSERT_EQUAL("abcd", other.join());

  other.clear();
  CPPUNIT_ASSERT_EQUAL(0, other.size());

  other = data;
  CPPUNIT_ASSERT_EQUAL(4, other.size());
  CPPUNIT_ASSERT_EQUAL("abcd", other.join());
}
