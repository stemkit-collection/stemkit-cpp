/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#include "InetAddressTest.h"
#include <sk/net/InetAddress.h>
#include <sk/util/Holder.cxx>
#include <sk/util/covariant.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::net::test::InetAddressTest);

sk::net::test::InetAddressTest::
InetAddressTest()
{
}

sk::net::test::InetAddressTest::
~InetAddressTest()
{
}

void
sk::net::test::InetAddressTest::
setUp()
{
  sk::net::InetAddress::clearCache();
}

void
sk::net::test::InetAddressTest::
tearDown()
{
}

void
sk::net::test::InetAddressTest::
test_creates_unresolved_ip4_address()
{
  sk::net::InetAddress& address = sk::net::InetAddress::getByAddress(sk::util::bytes(1) << 2 << 3 << 4);
  CPPUNIT_ASSERT_EQUAL("1.2.3.4", address.getHostAddress());
  CPPUNIT_ASSERT(address.isResolved() == false);
}

void
sk::net::test::InetAddressTest::
test_clones_ip4_address()
{
  sk::net::InetAddress& address = sk::net::InetAddress::getByAddress(sk::util::bytes(1) << 2 << 3 << 4);
  sk::util::Holder<sk::net::InetAddress> cloneHolder(sk::util::covariant<sk::net::InetAddress>(address.clone()));

  CPPUNIT_ASSERT_EQUAL("1.2.3.4", address.getHostAddress());
  CPPUNIT_ASSERT(address.isResolved() == false);
}
