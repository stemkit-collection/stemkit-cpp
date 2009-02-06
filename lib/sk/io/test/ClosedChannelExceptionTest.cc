/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ClosedChannelExceptionTest.h"
#include <sk/io/ClosedChannelException.h>
#include <sk/util/Class.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::io::test::ClosedChannelExceptionTest);

sk::io::test::ClosedChannelExceptionTest::
ClosedChannelExceptionTest()
{
}

sk::io::test::ClosedChannelExceptionTest::
~ClosedChannelExceptionTest()
{
}

void
sk::io::test::ClosedChannelExceptionTest::
setUp()
{
}

void
sk::io::test::ClosedChannelExceptionTest::
tearDown()
{
}

void
sk::io::test::ClosedChannelExceptionTest::
testThrow()
{
  try {
    throw ClosedChannelException();
  }
  catch(const sk::util::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Input/output: Closed channel", exception.getMessage());
    CPPUNIT_ASSERT_EQUAL("sk::io::ClosedChannelException", exception.getClass().getName());
  }
}
