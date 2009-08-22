/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ProbeTest.h"
#include "api/Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ProbeTest);

sk::util::test::ProbeTest::
ProbeTest()
{
}

sk::util::test::ProbeTest::
~ProbeTest()
{
}

void
sk::util::test::ProbeTest::
setUp()
{
}

void
sk::util::test::ProbeTest::
tearDown()
{
}

void
sk::util::test::ProbeTest::
testBasics()
{
  sk::util::test::Probe probe("abc");
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", probe.inspect());

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", sk_util_test_Probe_inspect(probe.get_c_handle(), buffer, sizeof(buffer)));
}
