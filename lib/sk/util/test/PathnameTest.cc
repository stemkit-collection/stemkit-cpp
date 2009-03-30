/*  vim: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PathnameTest.h"
#include <sk/util/Pathname.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PathnameTest);

sk::util::test::PathnameTest::
PathnameTest()
{
}

sk::util::test::PathnameTest::
~PathnameTest()
{
}

void
sk::util::test::PathnameTest::
setUp()
{
}

void
sk::util::test::PathnameTest::
tearDown()
{
}

void
sk::util::test::PathnameTest::
testJoin()
{
  CPPUNIT_ASSERT_EQUAL("a/b", Pathname("a").join(Pathname("b")).toString());
  CPPUNIT_ASSERT_EQUAL("a/b/c/d", Pathname("a/b/").join(Pathname("c/d")).toString());
  CPPUNIT_ASSERT_EQUAL("/c/d", Pathname("a/b/").join(Pathname("/c/d")).toString());
}

void
sk::util::test::PathnameTest::
testIsAbsolute()
{
  CPPUNIT_ASSERT_EQUAL(false, Pathname("a").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(false, Pathname("a/b").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("/a").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("\\a").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:a").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:a/b").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:/a").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:/a/b/").isAbsolute());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("host:/a").isAbsolute());
}

void
sk::util::test::PathnameTest::
testDirname()
{
  CPPUNIT_ASSERT_EQUAL(".", Pathname("aaa").dirname().toString());
  CPPUNIT_ASSERT_EQUAL(".", Pathname("").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("a", Pathname("a/b").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("a/b", Pathname("a/b/").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:a/b", Pathname("C:a/b/").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:/a", Pathname("C:/a/b").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("/", Pathname("/a").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:/", Pathname("C:/a").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:/", Pathname("C::::\\//\\").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:", Pathname("C:aaa").dirname().toString());
  CPPUNIT_ASSERT_EQUAL("C:", Pathname("C:").dirname().toString());

  Pathname location = "/a";
  Pathname parent = location.dirname();
  Pathname grandparent = parent.dirname();

  CPPUNIT_ASSERT_EQUAL("/", parent.toString());
  CPPUNIT_ASSERT_EQUAL("/", grandparent.toString());

  CPPUNIT_ASSERT(parent == grandparent);
}

void
sk::util::test::PathnameTest::
testBasename()
{
  CPPUNIT_ASSERT_EQUAL("abc", Pathname("abc").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("").basename());
  CPPUNIT_ASSERT_EQUAL("b", Pathname("/a/b").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("/a/b/").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("/").basename());
  CPPUNIT_ASSERT_EQUAL("aaa", Pathname("D:aaa").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("D:aaa/").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("D:").basename());
  CPPUNIT_ASSERT_EQUAL("", Pathname("D:/").basename());
}

void
sk::util::test::PathnameTest::
testLocation()
{
  CPPUNIT_ASSERT_EQUAL(".", Pathname("aaa").location());
  CPPUNIT_ASSERT_EQUAL(".", Pathname("").location());
  CPPUNIT_ASSERT_EQUAL("/", Pathname("/aaa").location());
  CPPUNIT_ASSERT_EQUAL("C:", Pathname("C:aaa/bbb").location());
  CPPUNIT_ASSERT_EQUAL("C:/", Pathname("C:\\aaa\\bbb").location());
}

void
sk::util::test::PathnameTest::
testExtension()
{
  CPPUNIT_ASSERT_EQUAL("a/b/ccc.i", Pathname("a//b/ccc.i", "log").toString());
  CPPUNIT_ASSERT_EQUAL("a/b/ccc.log", Pathname("a//b/ccc", "log").toString());
  CPPUNIT_ASSERT_EQUAL("a/b.c/ddd.log", Pathname("a//b.c///ddd", "log").toString());
  CPPUNIT_ASSERT_EQUAL("ddd.log", Pathname("ddd", "log").toString());
  CPPUNIT_ASSERT_EQUAL(".log", Pathname("", "log").toString());

  CPPUNIT_ASSERT_EQUAL("", Pathname("a/b/c").extension());
  CPPUNIT_ASSERT_EQUAL(".", Pathname("a/b/c.").extension());
  CPPUNIT_ASSERT_EQUAL(".zip", Pathname("a/b/c.zip").extension());
}

void 
sk::util::test::PathnameTest::
testIsTerminal()
{
  return;

  CPPUNIT_ASSERT_EQUAL(true, Pathname("").isTerminal());
  CPPUNIT_ASSERT_EQUAL(true, Pathname(".").isTerminal());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("./").isTerminal());

  CPPUNIT_ASSERT_EQUAL(true, Pathname("aaa").dirname().isTerminal());

  CPPUNIT_ASSERT_EQUAL(true, Pathname("/").isTerminal());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:/").isTerminal());
  CPPUNIT_ASSERT_EQUAL(true, Pathname("C:").isTerminal());

  CPPUNIT_ASSERT_EQUAL(false, Pathname("aaa").isTerminal());
  CPPUNIT_ASSERT_EQUAL(false, Pathname("C:/aaa").isTerminal());
  CPPUNIT_ASSERT_EQUAL(false, Pathname("C:aaa").isTerminal());
  CPPUNIT_ASSERT_EQUAL(false, Pathname("/aaa").isTerminal());
}

