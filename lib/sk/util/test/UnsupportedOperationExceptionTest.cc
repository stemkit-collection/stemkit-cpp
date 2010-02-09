/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "UnsupportedOperationExceptionTest.h"
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::UnsupportedOperationExceptionTest);

sk::util::test::UnsupportedOperationExceptionTest::
UnsupportedOperationExceptionTest()
{
}

sk::util::test::UnsupportedOperationExceptionTest::
~UnsupportedOperationExceptionTest()
{
}

void
sk::util::test::UnsupportedOperationExceptionTest::
setUp()
{
}

void
sk::util::test::UnsupportedOperationExceptionTest::
tearDown()
{
}

void
sk::util::test::UnsupportedOperationExceptionTest::
testThrow()
{
  try {
    throw UnsupportedOperationException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Unsupported operation: zzz", exception.what());
    CPPUNIT_ASSERT_EQUAL("sk::util::UnsupportedOperationException", exception.getClass().getName());
  }
}
