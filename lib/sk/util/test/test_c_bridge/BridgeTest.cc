/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "BridgeTest.h"
#include "api/Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::BridgeTest);

sk::util::test::BridgeTest::
BridgeTest()
{
}

sk::util::test::BridgeTest::
~BridgeTest()
{
}

void
sk::util::test::BridgeTest::
setUp()
{
}

void
sk::util::test::BridgeTest::
tearDown()
{
}

void
sk::util::test::BridgeTest::
testBasics()
{
  sk::util::test::Probe probe("abc");
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", probe.inspect());

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", sk_util_test_Probe_inspect(probe.get_c_handle(), buffer, sizeof(buffer)));
}
