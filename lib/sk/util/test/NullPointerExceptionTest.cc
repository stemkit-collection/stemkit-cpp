/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "NullPointerExceptionTest.h"
#include <sk/util/NullPointerException.h>
#include <sk/util/Class.h>

sk::util::test::NullPointerExceptionTest::
NullPointerExceptionTest()
{
}

sk::util::test::NullPointerExceptionTest::
~NullPointerExceptionTest()
{
}

void
sk::util::test::NullPointerExceptionTest::
setUp()
{
}

void
sk::util::test::NullPointerExceptionTest::
tearDown()
{
}

void
sk::util::test::NullPointerExceptionTest::
testThrow()
{
  try {
    throw NullPointerException("zzz");
  }
  catch(const Exception& exception) {
    CPPUNIT_ASSERT_EQUAL(String("ERROR:Null pointer:zzz"), exception.getMessage());
    CPPUNIT_ASSERT_EQUAL(String("sk::util::NullPointerException"), exception.getClass().getName());
  }
}
