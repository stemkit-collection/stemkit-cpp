/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringHashTest.h"
#include <sk/util/StringHash.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::StringHashTest);

sk::util::test::StringHashTest::
StringHashTest()
{
}

sk::util::test::StringHashTest::
~StringHashTest()
{
}

void
sk::util::test::StringHashTest::
setUp()
{
}

void
sk::util::test::StringHashTest::
testBasics()
{
  StringHash hash;

  CPPUNIT_ASSERT_EQUAL(true, hash.empty());
  hash["abc"] = "zzz";
  CPPUNIT_ASSERT_EQUAL(false, hash.empty());
  CPPUNIT_ASSERT_EQUAL(size_t(1), hash.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("zzz").inspect(), hash["abc"].inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("").inspect(), hash["aaa"].inspect());
}

void
sk::util::test::StringHashTest::
tearDown()
{
}
