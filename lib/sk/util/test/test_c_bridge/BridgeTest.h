/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_BRIDGETEST_H_
#define _SK_UTIL_TEST_BRIDGETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class BridgeTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::BridgeTest);
          CPPUNIT_TEST(testProbe);
          CPPUNIT_TEST(testProbeFactory);
          CPPUNIT_TEST(testProbeFactoryC);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          BridgeTest();
          virtual ~BridgeTest();
      
          void setUp();
          void tearDown();
          void testProbe();
          void testProbeFactory();
          void testProbeFactoryC();
      
        private:
          BridgeTest(const BridgeTest& other);
          BridgeTest& operator = (const BridgeTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_BRIDGETEST_H_ */