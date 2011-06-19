/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "NoSuchElementExceptionTest.h"
#include <sk/util/NoSuchElementException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::NoSuchElementExceptionTest);

sk::util::test::NoSuchElementExceptionTest::
NoSuchElementExceptionTest()
{
}

sk::util::test::NoSuchElementExceptionTest::
~NoSuchElementExceptionTest()
{
}

void
sk::util::test::NoSuchElementExceptionTest::
setUp()
{
}

void
sk::util::test::NoSuchElementExceptionTest::
tearDown()
{
}

void
sk::util::test::NoSuchElementExceptionTest::
testThrow()
{
  try {
    throw NoSuchElementException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("No such element: zzz", exception.what());
    CPPUNIT_ASSERT_EQUAL("sk::util::NoSuchElementException", exception.getClass().getName());
  }
}
