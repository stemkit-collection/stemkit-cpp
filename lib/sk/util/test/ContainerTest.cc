/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ContainerTest.h"
#include <sk/util/Container.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ContainerTest);

sk::util::test::ContainerTest::
ContainerTest()
{
}

sk::util::test::ContainerTest::
~ContainerTest()
{
}

void
sk::util::test::ContainerTest::
setUp()
{
}

void
sk::util::test::ContainerTest::
tearDown()
{
}

void
sk::util::test::ContainerTest::
testFromBuffer()
{
  Container c1("zzz\0bbb");
  CPPUNIT_ASSERT_EQUAL(3, c1.size());
  CPPUNIT_ASSERT_EQUAL(3, c1.length());
  CPPUNIT_ASSERT_EQUAL(String("\"zzz\""), c1.inspect());

  Container c2("zzz\0bbb", 7);
  CPPUNIT_ASSERT_EQUAL(7, c2.size());
  CPPUNIT_ASSERT_EQUAL(String("\"zzz\\x00bbb\""), c2.inspect());

  CPPUNIT_ASSERT_EQUAL(true, Container("abc", 0).isEmpty());
  CPPUNIT_ASSERT_EQUAL(0, Container(static_cast<const char*>(0), 34).size());
}

void
sk::util::test::ContainerTest::
testFromSize()
{
  Container c(4);
  CPPUNIT_ASSERT_EQUAL(4, c.size());
  CPPUNIT_ASSERT_EQUAL(String("\"\\x00\\x00\\x00\\x00\""), c.inspect());
}

void
sk::util::test::ContainerTest::
testFromString()
{
  String s = "Hello, world!!!";

  Container c1(s);
  CPPUNIT_ASSERT_EQUAL(15, c1.size());

  Container c2(s, 5);
  CPPUNIT_ASSERT_EQUAL(5, c2.size());
  CPPUNIT_ASSERT_EQUAL(Container("Hello").inspect(), c2.inspect());

  Container c3(s, 50);
  CPPUNIT_ASSERT_EQUAL(15, c3.size());
}

void
sk::util::test::ContainerTest::
testFromVector()
{
  std::vector<char> v(Container("abc", 4));
  Container c(v);

  CPPUNIT_ASSERT_EQUAL(4, c.size());
  CPPUNIT_ASSERT_EQUAL(String("\"abc\\x00\""), c.inspect());
}

void
sk::util::test::ContainerTest::
testFromAnother()
{
  Container c(Container("abc", 4));

  CPPUNIT_ASSERT_EQUAL(4, c.size());
  CPPUNIT_ASSERT_EQUAL(String("\"abc\\x00\""), c.inspect());
}

void
sk::util::test::ContainerTest::
testEmpty()
{
  CPPUNIT_ASSERT_EQUAL(0, Container().size());
  CPPUNIT_ASSERT_EQUAL(0, Container(0).size());
}
