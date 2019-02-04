/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "SystemExceptionTest.h"
#include <sk/util/IllegalStateException.h>
#include <sk/rt/SystemException.h>
#include <windows.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::win32::test::SystemExceptionTest);

sk::rt::win32::test::SystemExceptionTest::
SystemExceptionTest()
{
}

sk::rt::win32::test::SystemExceptionTest::
~SystemExceptionTest()
{
}

void
sk::rt::win32::test::SystemExceptionTest::
setUp()
{
}

void
sk::rt::win32::test::SystemExceptionTest::
tearDown()
{
}

void
sk::rt::win32::test::SystemExceptionTest::
testBadHandle()
{
  if(CloseHandle(0) != 0) {
    throw sk::util::IllegalStateException("CloseHandle() did not fail");
  }
  sk::rt::SystemException error("CloseHandle");
  CPPUNIT_ASSERT_EQUAL("Runtime: CloseHandle: 0: The handle is invalid.", error.what());
}
