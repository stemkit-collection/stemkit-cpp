/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "InterruptedExceptionTest.h"
#include <sk/util/InterruptedException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::InterruptedExceptionTest);

sk::util::test::InterruptedExceptionTest::
InterruptedExceptionTest()
{
}

sk::util::test::InterruptedExceptionTest::
~InterruptedExceptionTest()
{
}

void
sk::util::test::InterruptedExceptionTest::
setUp()
{
}

void
sk::util::test::InterruptedExceptionTest::
tearDown()
{
}

void
sk::util::test::InterruptedExceptionTest::
testThrow()
{
  try {
    throw InterruptedException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("Interrupted: zzz", exception.what());
    CPPUNIT_ASSERT_EQUAL("sk::util::InterruptedException", exception.getClass().getName());
  }
}
