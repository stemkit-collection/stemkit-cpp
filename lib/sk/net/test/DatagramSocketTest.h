/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_TEST_DATAGRAMSOCKETTEST_H_
#define _SK_NET_TEST_DATAGRAMSOCKETTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace net {
    namespace test {
      class DatagramSocketTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::net::test::DatagramSocketTest);
          CPPUNIT_TEST(test_transmits_simple_data);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          DatagramSocketTest();
          virtual ~DatagramSocketTest();
      
          void setUp();
          void tearDown();
          void test_transmits_simple_data();
      
        private:
          DatagramSocketTest(const DatagramSocketTest& other);
          DatagramSocketTest& operator = (const DatagramSocketTest& other);
      };
    }
  }
}

#endif /* _SK_NET_TEST_DATAGRAMSOCKETTEST_H_ */
