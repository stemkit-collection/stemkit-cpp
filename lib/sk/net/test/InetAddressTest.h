/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_NET_TEST_INETADDRESSTEST_H_
#define _SK_NET_TEST_INETADDRESSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace net {
    namespace test {
      class InetAddressTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::net::test::InetAddressTest);
          CPPUNIT_TEST(test_creates_unresolved_ip4_address);
          CPPUNIT_TEST(test_clones_ip4_address);
        CPPUNIT_TEST_SUITE_END();

        public:
          InetAddressTest();
          virtual ~InetAddressTest();

          void setUp();
          void tearDown();
          void test_creates_unresolved_ip4_address();
          void test_clones_ip4_address();

        private:
          InetAddressTest(const InetAddressTest& other);
          InetAddressTest& operator = (const InetAddressTest& other);
      };
    }
  }
}

#endif /* _SK_NET_TEST_INETADDRESSTEST_H_ */
