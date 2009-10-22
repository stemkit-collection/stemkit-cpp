/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "InsufficientMemoryExceptionTest.h"
#include <sk/util/InsufficientMemoryException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::InsufficientMemoryExceptionTest);

sk::util::test::InsufficientMemoryExceptionTest::
InsufficientMemoryExceptionTest()
{
}

sk::util::test::InsufficientMemoryExceptionTest::
~InsufficientMemoryExceptionTest()
{
}

void
sk::util::test::InsufficientMemoryExceptionTest::
setUp()
{
}

void
sk::util::test::InsufficientMemoryExceptionTest::
tearDown()
{
}

void
sk::util::test::InsufficientMemoryExceptionTest::
testThrow()
{
  try {
    throw InsufficientMemoryException("something", 279);
  }
  catch(const InsufficientMemoryException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Memory allocation: something: 279", exception.getMessage());
    CPPUNIT_ASSERT_EQUAL("sk::util::InsufficientMemoryException", exception.getClass().getName());
    CPPUNIT_ASSERT_EQUAL(size_t(279), exception.getRequestedAmount());
  }
}
