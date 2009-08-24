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
#include <sk/C/test/Probe.h>
#include <sk/C/test/ProbeFactory.h>
#include <sk/C/test/c_probe_factory.h>

#include "test_probe_factory.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::C::test::BridgeTest);

sk::C::test::BridgeTest::
BridgeTest()
{
}

sk::C::test::BridgeTest::
~BridgeTest()
{
}

void
sk::C::test::BridgeTest::
setUp()
{
  sk::C::test::Probe::resetInstanceCouner();
}

void
sk::C::test::BridgeTest::
tearDown()
{
}

void
sk::C::test::BridgeTest::
testProbe()
{
  sk::C::test::Probe probe("abc");
  CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"abc\"", probe.inspect());

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"abc\"", sk_c_test_Probe_inspect(probe.get_c_handle(), buffer, sizeof(buffer)));
}

void
sk::C::test::BridgeTest::
testProbeFactory()
{
  {
    sk::C::test::ProbeFactory factory;
    CPPUNIT_ASSERT_EQUAL(0, factory.getSize());

    CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"zzz\"", factory.makeProbe("zzz").inspect());
    CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"uuu\"", factory.makeProbe("uuu").inspect());

    CPPUNIT_ASSERT_EQUAL(2, factory.getSize());
    CPPUNIT_ASSERT_EQUAL(2, sk::C::test::Probe::getInstanceCouner());
  }
  CPPUNIT_ASSERT_EQUAL(0, sk::C::test::Probe::getInstanceCouner());
}

void
sk::C::test::BridgeTest::
testProbeFactoryC()
{
  sk_c_test_ProbeFactoryHandle* factory = sk_c_test_ProbeFactory_create();
  CPPUNIT_ASSERT_EQUAL(0, sk_c_test_ProbeFactory_getSize(factory));

  char buffer[80];
  CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"zzz\"", sk_c_test_Probe_inspect(sk_c_test_ProbeFactory_makeProbe(factory, "zzz"), buffer, sizeof(buffer)));
  CPPUNIT_ASSERT_EQUAL("sk::C::test::Probe=\"uuu\"", sk_c_test_Probe_inspect(sk_c_test_ProbeFactory_makeProbe(factory, "uuu"), buffer, sizeof(buffer)));

  CPPUNIT_ASSERT_EQUAL(2, sk_c_test_ProbeFactory_getSize(factory));
  CPPUNIT_ASSERT_EQUAL(2, sk_c_test_Probe_getInstanceCounter());

  sk_c_test_ProbeFactory_destroy(factory);
  CPPUNIT_ASSERT_EQUAL(0, sk_c_test_Probe_getInstanceCounter());
}

void
sk::C::test::BridgeTest::
testRealC()
{
  char buffer[1024];

  CPPUNIT_ASSERT_EQUAL("OK", test_probe_factory(buffer, sizeof(buffer)));
  CPPUNIT_ASSERT_EQUAL(0, sk::C::test::Probe::getInstanceCouner());
}
