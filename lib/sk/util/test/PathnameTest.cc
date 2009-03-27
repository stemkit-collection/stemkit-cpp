/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
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
