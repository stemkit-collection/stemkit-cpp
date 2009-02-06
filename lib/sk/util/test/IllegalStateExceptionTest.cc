/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "IllegalStateExceptionTest.h"
#include <sk/util/IllegalStateException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::IllegalStateExceptionTest);

sk::util::test::IllegalStateExceptionTest::
IllegalStateExceptionTest()
{
}

sk::util::test::IllegalStateExceptionTest::
~IllegalStateExceptionTest()
{
}

void
sk::util::test::IllegalStateExceptionTest::
setUp()
{
}

void
sk::util::test::IllegalStateExceptionTest::
tearDown()
{
}

void
sk::util::test::IllegalStateExceptionTest::
testThrow()
{
  try {
    throw IllegalStateException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Illegal state: zzz", exception.getMessage());
    CPPUNIT_ASSERT_EQUAL("sk::util::IllegalStateException", exception.getClass().getName());
  }
}
