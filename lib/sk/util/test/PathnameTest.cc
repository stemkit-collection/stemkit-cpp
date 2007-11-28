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
  Pathname p("aaa///bbb///ccc");
  CPPUNIT_ASSERT_EQUAL(String("aaa/bbb/ccc").inspect(), p.toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String("ccc").inspect(), p.basename().inspect());
  CPPUNIT_ASSERT_EQUAL(String("aaa/bbb").inspect(), p.dirname().inspect());

  CPPUNIT_ASSERT_EQUAL(false, p.isAbsolute());
  p.front("////zzz///");
  CPPUNIT_ASSERT_EQUAL(String("/zzz/aaa/bbb/ccc").inspect(), p.toString().inspect());
  CPPUNIT_ASSERT_EQUAL(true, p.isAbsolute());
  p.front("/uuu");
  CPPUNIT_ASSERT_EQUAL(String("/zzz/aaa/bbb").inspect(), p.dirname().inspect());
  CPPUNIT_ASSERT_EQUAL(String("ccc").inspect(), p.basename().inspect());
  CPPUNIT_ASSERT_EQUAL(true, p.isAbsolute());
}

void
sk::util::test::PathnameTest::
testExtension()
{
  CPPUNIT_ASSERT_EQUAL(String("a/b/ccc.i").inspect(), Pathname("a//b/ccc.i", "log").toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String("a/b/ccc.log").inspect(), Pathname("a//b/ccc", "log").toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String("a/b.c/ddd.log").inspect(), Pathname("a//b.c///ddd", "log").toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String("ddd.log").inspect(), Pathname("ddd", "log").toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String(".log").inspect(), Pathname("", "log").toString().inspect());
}
