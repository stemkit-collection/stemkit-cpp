/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_PROCESSTEST_
#define _SK_SYS_TEST_PROCESSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class ProcessTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::ProcessTest);
          // *GOOD* CPPUNIT_TEST(testTrueCommand);
          // *GOOD* CPPUNIT_TEST(testFalseCommand);
          // *GOOD* CPPUNIT_TEST(testExitCode);
          CPPUNIT_TEST(testKilled);
          // *FAILS* CPPUNIT_TEST(testNormalStop);
          // *GOOD* CPPUNIT_TEST(testForcedStop);
          // *GOOD* CPPUNIT_TEST(testRedirectInput);
          // *GOOD* CPPUNIT_TEST(testNoHangOnInputRead);
          // *GOOD* CPPUNIT_TEST(testSpawn);
          // *GOOD* CPPUNIT_TEST(testConfiguring);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ProcessTest();
          virtual ~ProcessTest();
          
          void setUp();
          void tearDown();
          void testTrueCommand();
          void testFalseCommand();
          void testExitCode();
          void testKilled();
          void testNormalStop();
          void testForcedStop();
          void testRedirectInput();
          void testNoHangOnInputRead();
          void testSpawn();
          void testConfiguring();
          
        private:
          ProcessTest(const ProcessTest& other);
          ProcessTest& operator = (const ProcessTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_PROCESSTEST_ */
