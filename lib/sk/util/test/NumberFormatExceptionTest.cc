/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "NumberFormatExceptionTest.h"
#include <sk/util/NumberFormatException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::NumberFormatExceptionTest);

sk::util::test::NumberFormatExceptionTest::
NumberFormatExceptionTest()
{
}

sk::util::test::NumberFormatExceptionTest::
~NumberFormatExceptionTest()
{
}

void
sk::util::test::NumberFormatExceptionTest::
setUp()
{
}

void
sk::util::test::NumberFormatExceptionTest::
tearDown()
{
}

void
sk::util::test::NumberFormatExceptionTest::
testThrow()
{
  try {
    throw NumberFormatException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL(String("ERROR:Wrong number format:zzz"), exception.getMessage());
    CPPUNIT_ASSERT_EQUAL(String("sk::util::NumberFormatException"), exception.getClass().getName());
  }
}
