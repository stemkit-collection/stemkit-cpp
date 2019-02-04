/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "DatagramSocketTest.h"
#include <sk/net/DatagramSocket.h>
#include <sk/net/ip4/InetAddress.h>
#include <sk/net/BindException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::net::test::DatagramSocketTest);

sk::net::test::DatagramSocketTest::
DatagramSocketTest()
{
}

sk::net::test::DatagramSocketTest::
~DatagramSocketTest()
{
}

void
sk::net::test::DatagramSocketTest::
setUp()
{
}

void
sk::net::test::DatagramSocketTest::
tearDown()
{
}

void
sk::net::test::DatagramSocketTest::
test_transmits_simple_data()
{
  sk::net::DatagramSocket s1;
  sk::net::DatagramSocket s2;
  
  s1.send(sk::util::Container("Hello"), sk::net::ip4::InetAddress::getLoopbackAddress(), s2.localPort());

  std::vector<char> buffer(127, 0);
  const sk::net::InetSocketAddress endpoint = s2.receive(buffer);

  CPPUNIT_ASSERT_EQUAL(size_t(5), buffer.size());
  CPPUNIT_ASSERT_EQUAL("Hello", sk::util::Container(buffer).toString());

  CPPUNIT_ASSERT_EQUAL(s1.localPort(), endpoint.getPort());
  CPPUNIT_ASSERT(endpoint.getAddress().isLoopbackAddress() == true);
}

void
sk::net::test::DatagramSocketTest::
test_fails_on_port_in_use()
{
  sk::net::DatagramSocket s1;
  try {
    sk::net::DatagramSocket s2(s1.localPort());
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::net::BindException& exception) {
    CPPUNIT_ASSERT_EQUAL(s1.localPort(), exception.getPort());
  }
}
