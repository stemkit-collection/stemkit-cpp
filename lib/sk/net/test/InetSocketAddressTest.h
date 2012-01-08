/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky <bystr@mac.com>
*/

#ifndef _SK_NET_TEST_INETSOCKETADDRESSTEST_H_
#define _SK_NET_TEST_INETSOCKETADDRESSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace net {
    namespace test {
      class InetSocketAddressTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::net::test::InetSocketAddressTest);
          CPPUNIT_TEST(test_creates_unresolved_ip4_address);
          CPPUNIT_TEST(test_creates_wildcard_address);
        CPPUNIT_TEST_SUITE_END();

        public:
          InetSocketAddressTest();
          virtual ~InetSocketAddressTest();

          void setUp();
          void tearDown();
          void test_creates_unresolved_ip4_address();
          void test_creates_wildcard_address();

        private:
          InetSocketAddressTest(const InetSocketAddressTest& other);
          InetSocketAddressTest& operator = (const InetSocketAddressTest& other);
      };
    }
  }
}

#endif /* _SK_NET_TEST_INETSOCKETADDRESSTEST_H_ */
