/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_BITSETTEST_H_
#define _SK_UTIL_TEST_BITSETTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class BitsetTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::BitsetTest);
          CPPUNIT_TEST(testEmpty);
          CPPUNIT_TEST(testUpperBounds);
          CPPUNIT_TEST(testImplicitCapacityAdjustment);
          CPPUNIT_TEST(testBulk);
          CPPUNIT_TEST(testCompact);
        CPPUNIT_TEST_SUITE_END();

        public:
          BitsetTest();
          virtual ~BitsetTest();

          void setUp();
          void tearDown();
          void testEmpty();
          void testUpperBounds();
          void testImplicitCapacityAdjustment();
          void testBulk();
          void testCompact();

        private:
          BitsetTest(const BitsetTest& other);
          BitsetTest& operator = (const BitsetTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_BITSETTEST_H_ */
