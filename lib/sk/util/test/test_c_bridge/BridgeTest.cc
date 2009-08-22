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
#include "api/ProbeFactory.h"
#include "api/c_probe_factory.h"

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
testProbe()
{
  sk::util::test::Probe probe("abc");
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", probe.inspect());

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"abc\"", sk_util_test_Probe_inspect(probe.get_c_handle(), buffer, sizeof(buffer)));
}

void
sk::util::test::BridgeTest::
testProbeFactory()
{
  sk::util::test::ProbeFactory factory;
  CPPUNIT_ASSERT_EQUAL(0, factory.getSize());

  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"zzz\"", factory.makeProbe("zzz").inspect());
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"uuu\"", factory.makeProbe("uuu").inspect());

  CPPUNIT_ASSERT_EQUAL(2, factory.getSize());
}

void
sk::util::test::BridgeTest::
testProbeFactoryC()
{
  sk_util_test_ProbeFactoryHandle* factory = sk_util_test_ProbeFactory_create();
  CPPUNIT_ASSERT_EQUAL(0, sk_util_test_ProbeFactory_getSize(factory));

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"zzz\"", sk_util_test_Probe_inspect(sk_util_test_ProbeFactory_makeProbe(factory, "zzz"), buffer, sizeof(buffer)));
  CPPUNIT_ASSERT_EQUAL("sk::util::test::Probe=\"uuu\"", sk_util_test_Probe_inspect(sk_util_test_ProbeFactory_makeProbe(factory, "uuu"), buffer, sizeof(buffer)));

  CPPUNIT_ASSERT_EQUAL(2, sk_util_test_ProbeFactory_getSize(factory));
  sk_util_test_ProbeFactory_destroy(factory);
}


