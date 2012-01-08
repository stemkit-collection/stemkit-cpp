/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "BooleanTest.h"
#include <sk/util/Boolean.h>
#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::BooleanTest);

sk::util::test::BooleanTest::
BooleanTest()
{
}

sk::util::test::BooleanTest::
~BooleanTest()
{
}

void
sk::util::test::BooleanTest::
setUp()
{
}

void
sk::util::test::BooleanTest::
tearDown()
{
}

void
sk::util::test::BooleanTest::
testConstants()
{
  CPPUNIT_ASSERT_EQUAL(true, Boolean::B_TRUE.booleanValue());
  CPPUNIT_ASSERT_EQUAL(false, Boolean::B_FALSE.booleanValue());
}

void
sk::util::test::BooleanTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL(true, Boolean(true).booleanValue());
  CPPUNIT_ASSERT_EQUAL(false, Boolean(false).booleanValue());
}


void
sk::util::test::BooleanTest::
testParse()
{
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("true"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("TRUE"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("TrUe"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("yes"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("YES"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("on"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("On"));
  CPPUNIT_ASSERT_EQUAL(true, Boolean::parseBoolean("T"));

  CPPUNIT_ASSERT_EQUAL(false, Boolean::parseBoolean("false"));
  CPPUNIT_ASSERT_EQUAL(false, Boolean::parseBoolean("FALSE"));
  CPPUNIT_ASSERT_EQUAL(false, Boolean::parseBoolean("zzz"));
}

void
sk::util::test::BooleanTest::
testValueOf()
{
  CPPUNIT_ASSERT_EQUAL(true, Boolean::valueOf(true).booleanValue());
  CPPUNIT_ASSERT_EQUAL(false, Boolean::valueOf(false).booleanValue());
  CPPUNIT_ASSERT_EQUAL(true, Boolean::valueOf("true").booleanValue());
  CPPUNIT_ASSERT_EQUAL(false, Boolean::valueOf("false").booleanValue());
}

void
sk::util::test::BooleanTest::
testToString()
{
  CPPUNIT_ASSERT_EQUAL(String("true").inspect(), Boolean(true).toString().inspect());
  CPPUNIT_ASSERT_EQUAL(String("false").inspect(), Boolean(false).toString().inspect());

  CPPUNIT_ASSERT_EQUAL(String("true"), Boolean(true).inspect());
  CPPUNIT_ASSERT_EQUAL(String("false"), Boolean(false).inspect());
}

void
sk::util::test::BooleanTest::
testStreamOutput()
{
  std::ostringstream stream;
  stream << Boolean(true) << ':' << Boolean(false);

  CPPUNIT_ASSERT_EQUAL(std::string("true:false"), stream.str());
}
