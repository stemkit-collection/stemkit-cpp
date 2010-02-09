/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ExceptionTest.h"
#include <sk/util/Exception.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ExceptionTest);

sk::util::test::ExceptionTest::
ExceptionTest()
{
}

sk::util::test::ExceptionTest::
~ExceptionTest()
{
}

void
sk::util::test::ExceptionTest::
setUp()
{
}

void
sk::util::test::ExceptionTest::
tearDown()
{
}

void
sk::util::test::ExceptionTest::
testThrow()
{
  try {
    throw sk::util::Exception("abcd");
  }
  catch(const sk::util::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("abcd", exception.getMessage());
    CPPUNIT_ASSERT_EQUAL("ERROR: abcd", String(exception.what()));
  }
}

void
sk::util::test::ExceptionTest::
testStandard()
{
  try {
    throw sk::util::Exception("abcd");
  }
  catch(const std::exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: abcd", exception.what());
  }
}
