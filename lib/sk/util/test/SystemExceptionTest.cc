/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "SystemExceptionTest.h"
#include <sk/util/SystemException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::SystemExceptionTest);

sk::util::test::SystemExceptionTest::
SystemExceptionTest()
{
}

sk::util::test::SystemExceptionTest::
~SystemExceptionTest()
{
}

void
sk::util::test::SystemExceptionTest::
setUp()
{
}

void
sk::util::test::SystemExceptionTest::
tearDown()
{
}

void
sk::util::test::SystemExceptionTest::
testThrow()
{
  try {
    throw SystemException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL(String("ERROR:System:zzz"), exception.getMessage());
    CPPUNIT_ASSERT_EQUAL(String("sk::util::SystemException"), exception.getClass().getName());
  }
}
