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
