/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "IndexOutOfBoundsExceptionTest.h"
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::IndexOutOfBoundsExceptionTest);

sk::util::test::IndexOutOfBoundsExceptionTest::
IndexOutOfBoundsExceptionTest()
{
}

sk::util::test::IndexOutOfBoundsExceptionTest::
~IndexOutOfBoundsExceptionTest()
{
}

void
sk::util::test::IndexOutOfBoundsExceptionTest::
setUp()
{
}

void
sk::util::test::IndexOutOfBoundsExceptionTest::
tearDown()
{
}

void
sk::util::test::IndexOutOfBoundsExceptionTest::
testThrow()
{
  try {
    throw IndexOutOfBoundsException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("Index out of bounds: zzz", exception.what());
    CPPUNIT_ASSERT_EQUAL("sk::util::IndexOutOfBoundsException", exception.getClass().getName());
  }
}
