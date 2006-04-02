/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "StringTest.h"
#include <sk/util/String.h>
#include <sk/util/Class.h>

sk::util::test::StringTest::
StringTest()
{
}

sk::util::test::StringTest::
~StringTest()
{
}

void
sk::util::test::StringTest::
setUp()
{
}

void
sk::util::test::StringTest::
tearDown()
{
}

void
sk::util::test::StringTest::
testCreateEmpty()
{
  String s;

  CPPUNIT_ASSERT_EQUAL(std::string("sk::util::String"), std::string(s.getClass().getName()));
  CPPUNIT_ASSERT_EQUAL(std::string(), std::string(s));
}

void
sk::util::test::StringTest::
testCreateFromBuffer()
{
  CPPUNIT_ASSERT_EQUAL(std::string("abcdefg"), std::string(String("abcdefg")));
  CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(String("abcdefg", 3)));
}
