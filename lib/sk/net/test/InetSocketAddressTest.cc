/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include "InetSocketAddressTest.h"
#include <sk/net/InetSocketAddress.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::net::test::InetSocketAddressTest);

sk::net::test::InetSocketAddressTest::
InetSocketAddressTest()
{
}

sk::net::test::InetSocketAddressTest::
~InetSocketAddressTest()
{
}

void
sk::net::test::InetSocketAddressTest::
setUp()
{
  sk::net::InetAddress::clearCache();
}

void
sk::net::test::InetSocketAddressTest::
tearDown()
{
}

void
sk::net::test::InetSocketAddressTest::
test_creates_unresolved_ip4_address()
{
  sk::net::InetSocketAddress address(sk::net::InetAddress::getByAddress(sk::util::bytes(2) << 3 << 4 << 5), 45);
  CPPUNIT_ASSERT_EQUAL("2.3.4.5", address.getHostName());
  CPPUNIT_ASSERT_EQUAL(uint16_t(45), address.getPort());
  CPPUNIT_ASSERT(address.isResolved() == false);
}

void
sk::net::test::InetSocketAddressTest::
test_creates_wildcard_address()
{
  sk::net::InetSocketAddress address(79);
  CPPUNIT_ASSERT_EQUAL(uint16_t(79), address.getPort());
  CPPUNIT_ASSERT(address.getAddress().isAnyLocalAddress() == true);
  CPPUNIT_ASSERT(address.getAddress().isLoopbackAddress() == false);
  CPPUNIT_ASSERT(address.getAddress().isMulticastAddress() == false);
}
