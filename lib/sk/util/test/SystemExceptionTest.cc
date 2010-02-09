/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "SystemExceptionTest.h"
#include <sk/util/SystemException.h>
#include <sk/util/Class.h>
#include <errno.h>

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
    errno = 0;
    throw SystemException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT(exception.getMessage().startsWith("System: zzz: 0:"));
    CPPUNIT_ASSERT_EQUAL("sk::util::SystemException", exception.getClass().getName());
  }
}
