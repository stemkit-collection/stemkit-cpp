/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "IntegerTest.h"
#include <sk/util/Integer.h>
#include <sk/util/String.h>
#include <sk/util/Class.h>
#include <sk/util/NumberFormatException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::IntegerTest);

sk::util::test::IntegerTest::
IntegerTest()
{
}

sk::util::test::IntegerTest::
~IntegerTest()
{
}

void
sk::util::test::IntegerTest::
setUp()
{
}

void
sk::util::test::IntegerTest::
tearDown()
{
}

void
sk::util::test::IntegerTest::
testClassName()
{
  CPPUNIT_ASSERT_EQUAL(String("sk::util::Integer"), Integer(0).getClass().getName());
}

void
sk::util::test::IntegerTest::
testStaticToString()
{
  CPPUNIT_ASSERT_EQUAL(String("0"), Integer::toString(0));

  CPPUNIT_ASSERT_EQUAL(String("1"), Integer::toString(1));
  CPPUNIT_ASSERT_EQUAL(String("21"), Integer::toString(21));
  CPPUNIT_ASSERT_EQUAL(String("12345"), Integer::toString(12345));

  CPPUNIT_ASSERT_EQUAL(String("-1"), Integer::toString(-1));
  CPPUNIT_ASSERT_EQUAL(String("-43210"), Integer::toString(-43210));
}

void
sk::util::test::IntegerTest::
testStaticToHexString()
{
  CPPUNIT_ASSERT_EQUAL(String("0"), Integer::toString(0x0, 16));
  CPPUNIT_ASSERT_EQUAL(String("ff"), Integer::toString(0xff, 16));
  CPPUNIT_ASSERT_EQUAL(String("1234abc"), Integer::toString(0x1234abc, 16));
}

void
sk::util::test::IntegerTest::
testParseInt()
{
  CPPUNIT_ASSERT_EQUAL(456, Integer::parseInt("456"));
  CPPUNIT_ASSERT_THROW(Integer::parseInt("abc"), NumberFormatException);

  CPPUNIT_ASSERT_EQUAL(0x123fc, Integer::parseInt("123fc", 16));
  CPPUNIT_ASSERT_EQUAL(0x123fc, Integer::parseInt("123FC", 16));
  CPPUNIT_ASSERT_THROW(Integer::parseInt("123FG"), NumberFormatException);

}

void
sk::util::test::IntegerTest::
testParseIntGuess()
{
  CPPUNIT_ASSERT_EQUAL(0x12, Integer::parseInt("0x12"));
  CPPUNIT_ASSERT_EQUAL(0x67B, Integer::parseInt("0X67b"));
  CPPUNIT_ASSERT_EQUAL(0x25, Integer::parseInt("0b100101"));
  CPPUNIT_ASSERT_EQUAL(0764, Integer::parseInt("0764"));
  
  CPPUNIT_ASSERT_EQUAL(1024, Integer::parseInt("1K"));
  CPPUNIT_ASSERT_EQUAL(15 * 1024, Integer::parseInt("15K"));

  CPPUNIT_ASSERT_EQUAL(1024 * 1024, Integer::parseInt("1M"));
  CPPUNIT_ASSERT_EQUAL(10 * 1024 * 1024, Integer::parseInt("10M"));
}
