/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_CAPPEDSTRINGSTEST_H_
#define _SK_UTIL_TEST_CAPPEDSTRINGSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class CappedStringsTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::CappedStringsTest);
          CPPUNIT_TEST(testCap);
          CPPUNIT_TEST(testNoCap);
        CPPUNIT_TEST_SUITE_END();

        public:
          CappedStringsTest();
          virtual ~CappedStringsTest();

          void setUp();
          void tearDown();
          void testCap();
          void testNoCap();

        private:
          CappedStringsTest(const CappedStringsTest& other);
          CappedStringsTest& operator = (const CappedStringsTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_CAPPEDSTRINGSTEST_H_ */
