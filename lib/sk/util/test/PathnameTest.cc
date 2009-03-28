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
testBasics()
{
  Pathname p("aaa///bbb\\ccc");
  CPPUNIT_ASSERT_EQUAL("aaa/bbb/ccc", p.toString());
  CPPUNIT_ASSERT_EQUAL("ccc", p.basename());
  CPPUNIT_ASSERT_EQUAL("aaa/bbb", p.dirname());

  CPPUNIT_ASSERT_EQUAL(false, p.isAbsolute());
  p.front("/\\\\/zzz///");
  CPPUNIT_ASSERT_EQUAL("/zzz/aaa/bbb/ccc", p.toString());
  CPPUNIT_ASSERT_EQUAL(true, p.isAbsolute());
  p.front("/uuu");
  CPPUNIT_ASSERT_EQUAL("/zzz/aaa/bbb", p.dirname());
  CPPUNIT_ASSERT_EQUAL("ccc", p.basename());
  CPPUNIT_ASSERT_EQUAL(true, p.isAbsolute());
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
  CPPUNIT_ASSERT_EQUAL(".", Pathname("aaa").dirname());
  CPPUNIT_ASSERT_EQUAL(".", Pathname("").dirname());
  CPPUNIT_ASSERT_EQUAL("a", Pathname("a/b").dirname());
  CPPUNIT_ASSERT_EQUAL("a/b", Pathname("a/b/").dirname());
  CPPUNIT_ASSERT_EQUAL("C:a/b", Pathname("C:a/b/").dirname());
  CPPUNIT_ASSERT_EQUAL("C:/a", Pathname("C:/a/b").dirname());
  CPPUNIT_ASSERT_EQUAL("/", Pathname("/a").dirname());
  CPPUNIT_ASSERT_EQUAL("C:/", Pathname("C:/a").dirname());
  CPPUNIT_ASSERT_EQUAL("C:/", Pathname("C::::\\//\\").dirname());
  CPPUNIT_ASSERT_EQUAL("C:", Pathname("C:aaa").dirname());
  CPPUNIT_ASSERT_EQUAL("C:", Pathname("C:").dirname());
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
