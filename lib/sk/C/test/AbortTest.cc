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
#include <sk/C/test/Probe.h>
#include <sk/C/test/c_probe.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::C::test::AbortTest);

static bool abort_raised = false;

extern "C" 
void abort() 
{
  if(abort_raised == true) {
    std::cerr << "!!! ANOTHER ABORT ACTIVATED. EXITTING !!!";
    *((int*)1) = -1;
    _exit(3);
  }
  abort_raised = true;
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
  abort_raised = false;
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
  try {
    abort();
    CPPUNIT_FAIL("No expected exception.");
  }
  catch(const sk::util::SystemExit& exception) {
    abort_raised = false;
  }
}

void
sk::C::test::AbortTest::
testAbortsOnNullHandle()
{
  try {
    char buffer[512];
    sk_c_test_Probe_inspect(0, buffer, sizeof(buffer));
    CPPUNIT_FAIL("Not aborted as expected.");
  }
  catch(const sk::util::SystemExit& exception) {
    abort_raised = false;
  }
}

void
sk::C::test::AbortTest::
testAbortsOnBadBuffer()
{
  char buffer[512];
  sk::C::test::Probe probe("abc");

  try {
    sk_c_test_Probe_inspect(probe.get_c_handle(), buffer, sizeof(buffer));
  }
  catch(const sk::util::SystemExit& exception) {
    CPPUNIT_FAIL("Unexpectedly aborted.");
  }

  try {
    sk_c_test_Probe_inspect(probe.get_c_handle(), 0, sizeof(buffer));
    CPPUNIT_FAIL("Not aborted as expected.");
  }
  catch(const sk::util::SystemExit& exception) {
    abort_raised = false;
  }

  try {
    sk_c_test_Probe_inspect(probe.get_c_handle(), buffer, 0);
    CPPUNIT_FAIL("Not aborted as expected.");
  }
  catch(const sk::util::SystemExit& exception) {
    abort_raised = false;
  }
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
    CPPUNIT_FAIL("Unexpectedly aborted.");
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
    CPPUNIT_FAIL("Not aborted as expected.");
  }
  catch(const sk::util::SystemExit& exception) {
    abort_raised = false;
  }
}
