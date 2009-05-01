/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_TEST_COVARIANTWORKAROUNDTEST_H_
#define _SK_UTIL_TEST_COVARIANTWORKAROUNDTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class CovariantWorkaroundTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::CovariantWorkaroundTest);
          CPPUNIT_TEST(testProbe);
          CPPUNIT_TEST(testCastSucceeds);
          CPPUNIT_TEST(testFailedCastDeletesProbe);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          CovariantWorkaroundTest();
          virtual ~CovariantWorkaroundTest();
      
          void setUp();
          void tearDown();
          void testProbe();
          void testCastSucceeds();
          void testFailedCastDeletesProbe();
      
        private:
          CovariantWorkaroundTest(const CovariantWorkaroundTest& other);
          CovariantWorkaroundTest& operator = (const CovariantWorkaroundTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_COVARIANTWORKAROUNDTEST_H_ */
