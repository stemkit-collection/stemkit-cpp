/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_TEST_TIMERTEST_H_
#define _SK_RT_TEST_TIMERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace test {
      class TimerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::test::TimerTest);
          CPPUNIT_TEST(testTicking);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          TimerTest();
          virtual ~TimerTest();
      
          void setUp();
          void tearDown();
          void testTicking();
      
        private:
          TimerTest(const TimerTest& other);
          TimerTest& operator = (const TimerTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TEST_TIMERTEST_H_ */
