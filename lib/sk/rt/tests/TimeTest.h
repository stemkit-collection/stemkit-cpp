/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_TESTS_TIMETEST_H_
#define _SK_RT_TESTS_TIMETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class TimeTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::TimeTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testOrdering);
          CPPUNIT_TEST(testSort);
        CPPUNIT_TEST_SUITE_END();

        public:
          TimeTest();
          virtual ~TimeTest();

          void setUp();
          void tearDown();
          void testBasics();
          void testOrdering();
          void testSort();

        private:
          TimeTest(const TimeTest& other);
          TimeTest& operator = (const TimeTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_TIMETEST_H_ */
