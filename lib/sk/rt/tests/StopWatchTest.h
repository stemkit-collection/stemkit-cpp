/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_TESTS_STOPWATCHTEST_H_
#define _SK_RT_TESTS_STOPWATCHTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class StopWatchTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::StopWatchTest);
          CPPUNIT_TEST(testTicking);
          CPPUNIT_TEST(testNotStarted);
          CPPUNIT_TEST(testChangesUntilStopped);
          CPPUNIT_TEST(testInspect);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          StopWatchTest();
          virtual ~StopWatchTest();
      
          void setUp();
          void tearDown();
          void testTicking();
          void testNotStarted();
          void testChangesUntilStopped();
          void testInspect();
      
        private:
          StopWatchTest(const StopWatchTest& other);
          StopWatchTest& operator = (const StopWatchTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_STOPWATCHTEST_H_ */
