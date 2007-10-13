/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_TESTS_LOGGERTEST_
#define _SK_RT_TESTS_LOGGERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class LoggerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::LoggerTest);
          CPPUNIT_TEST(testCreateName);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          LoggerTest();
          virtual ~LoggerTest();
          
          void setUp();
          void tearDown();
          void testCreateName();
          
        private:
          LoggerTest(const LoggerTest& other);
          LoggerTest& operator = (const LoggerTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_LOGGERTEST_ */
