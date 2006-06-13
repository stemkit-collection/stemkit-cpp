/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "MissingResourceExceptionTest.h"
#include <sk/util/MissingResourceException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::MissingResourceExceptionTest);

sk::util::test::MissingResourceExceptionTest::
MissingResourceExceptionTest()
{
}

sk::util::test::MissingResourceExceptionTest::
~MissingResourceExceptionTest()
{
}

void
sk::util::test::MissingResourceExceptionTest::
setUp()
{
}

void
sk::util::test::MissingResourceExceptionTest::
tearDown()
{
}

void
sk::util::test::MissingResourceExceptionTest::
testThrow()
{
  try {
    throw MissingResourceException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL(String("ERROR:Missing resource:zzz"), exception.getMessage());
    CPPUNIT_ASSERT_EQUAL(String("sk::util::MissingResourceException"), exception.getClass().getName());
  }
}
