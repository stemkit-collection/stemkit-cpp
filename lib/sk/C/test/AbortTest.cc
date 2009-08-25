/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "AbortTest.h"
#include <sk/util/SystemExit.h>
#include <sk/c/test/Probe.h>
#include <sk/c/test/c_probe.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::C::test::AbortTest);

static bool abort_raised = false;

extern "C" 
void abort() 
{
  throw sk::util::SystemExit(0, "aborted");
}

sk::C::test::AbortTest::
AbortTest()
{
}

sk::C::test::AbortTest::
~AbortTest()
{
}

void
sk::C::test::AbortTest::
setUp()
{
}

void
sk::C::test::AbortTest::
tearDown()
{
}

void
sk::C::test::AbortTest::
testAbortWrapper()
{
  CPPUNIT_ASSERT_THROW(abort(), sk::util::SystemExit);
}

void
sk::C::test::AbortTest::
testCanContinueAfterClear()
{
  try {
    sk::C::test::Probe probe("abc");
    sk_c_test_ProbeHandle* handle = probe.get_c_handle();
    
    char error_buffer[512];
    sk_c_test_Probe_raiseException(handle, "abc");
    CPPUNIT_ASSERT(sk_c_handle_isError(sk_c_test_ProbeHandle_toHandle(handle)));

    sk_c_handle_clearError(sk_c_test_ProbeHandle_toHandle(handle));
    CPPUNIT_ASSERT(!sk_c_handle_isError(sk_c_test_ProbeHandle_toHandle(handle)));

    sk_c_test_Probe_inspect(handle, error_buffer, sizeof(error_buffer));
  }
  catch(const sk::util::SystemExit& exception) {
    CPPUNIT_FAIL("Unexpectedly aborted");
  }
}

void 
sk::C::test::AbortTest::
testAbortsOnNextCallWhenNotCleared()
{
  try {
    sk::C::test::Probe probe("abc");
    sk_c_test_ProbeHandle* handle = probe.get_c_handle();
    
    char error_buffer[512];
    sk_c_test_Probe_raiseException(handle, "abc");
    CPPUNIT_ASSERT(sk_c_handle_isError(sk_c_test_ProbeHandle_toHandle(handle)));

    // Deleberatelly not clearing here, otherwise the test would fail.
    // sk_c_handle_clearError(sk_c_test_ProbeHandle_toHandle(handle));

    sk_c_test_Probe_inspect(handle, error_buffer, sizeof(error_buffer));
    CPPUNIT_FAIL("Not aborted as expected");
  }
  catch(const sk::util::SystemExit& exception) {}
}
