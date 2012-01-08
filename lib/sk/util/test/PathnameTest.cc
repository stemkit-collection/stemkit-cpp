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
testEmpty()
{
  sk::util::Pathname pathname("  ");

  CPPUNIT_ASSERT(pathname.isEmpty() == true);
  CPPUNIT_ASSERT(pathname.isAbsolute() == false);
  CPPUNIT_ASSERT(pathname.isExplicit() == false);
  //TODO: CPPUNIT_ASSERT(pathname.isTerminal() == false);

  CPPUNIT_ASSERT_EQUAL(".", pathname.dirname().toString());
  CPPUNIT_ASSERT_EQUAL(".", pathname.location());
  CPPUNIT_ASSERT_EQUAL("", pathname.extension());
  CPPUNIT_ASSERT_EQUAL("", pathname.basename());

  CPPUNIT_ASSERT_EQUAL("bbb", ("bbb" + pathname).toString());
  CPPUNIT_ASSERT_EQUAL("aaa", (pathname + "aaa").toString());
}

void
sk::util::test::PathnameTest::
testPlus()
{
  CPPUNIT_ASSERT_EQUAL("a/b", (Pathname("a") + Pathname("b")).toString());
  CPPUNIT_ASSERT_EQUAL("a/b/c/d", ("a/b/" + Pathname("c/d")).toString());
  CPPUNIT_ASSERT_EQUAL("/c/d", (Pathname("a/b/") + "/c/d").toString());
}

void
sk::util::test::PathnameTest::
testJoinOther()
{
  CPPUNIT_ASSERT_EQUAL("a/b", Pathname("a").join(Pathname("b")).toString());
  CPPUNIT_ASSERT_EQUAL("a/b/c/d", Pathname("a/b/").join(Pathname("c/d")).toString());
  CPPUNIT_ASSERT_EQUAL("/c/d", Pathname("a/b/").join(Pathname("/c/d")).toString());
}

void
sk::util::test::PathnameTest::
testJoinString()
{
  CPPUNIT_ASSERT_EQUAL("/b", Pathname("/").join("b").toString());
  CPPUNIT_ASSERT_EQUAL("/a/b", Pathname("/a").join("b").toString());
  CPPUNIT_ASSERT_EQUAL("/a/b", Pathname("/a//").join("b").toString());
  CPPUNIT_ASSERT_EQUAL("/b", Pathname("/a//").join("/b").toString());

  CPPUNIT_ASSERT_EQUAL("C:/b", Pathname("C:/").join("b").toString());
  CPPUNIT_ASSERT_EQUAL("D:b", Pathname("C:/").join("D:b").toString());

  CPPUNIT_ASSERT_EQUAL("a/b", Pathname("a").join("b").toString());
  CPPUNIT_ASSERT_EQUAL("a/b/c/d", Pathname("a/b/").join("c/d").toString());
  CPPUNIT_ASSERT_EQUAL("/c/d", Pathname("a/b/").join("/c/d").toString());
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

void
sk::util::test::PathnameTest::
testWindowsResourcePath()
{
  Pathname path("\\\\Resource\\a\\b/c");

  CPPUNIT_ASSERT(path.isEmpty() == false);
  CPPUNIT_ASSERT(path.isAbsolute() == true);
  CPPUNIT_ASSERT(path.isExplicit() == true);
  // CPPUNIT_ASSERT(path.isTerminal() == false);
  // CPPUNIT_ASSERT(Pathname("\\\\Resource").isTerminal() == false);
  // CPPUNIT_ASSERT(Pathname("\\\\Resource/").isTerminal() == true);

  CPPUNIT_ASSERT_EQUAL("\\\\Resource/a/b/c", path.toString());
  CPPUNIT_ASSERT_EQUAL("\\\\Resource/a/b", path.dirname().toString());
  CPPUNIT_ASSERT_EQUAL("c", path.basename());
  CPPUNIT_ASSERT_EQUAL("", path.extension());
  CPPUNIT_ASSERT_EQUAL("\\\\Resource/", path.location());
}

