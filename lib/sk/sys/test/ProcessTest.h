/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_PROCESSTEST_
#define _SK_IO_TEST_PROCESSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class ProcessTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::ProcessTest);
          CPPUNIT_TEST(testTrueCommand);
          CPPUNIT_TEST(testFalseCommand);
          CPPUNIT_TEST(testExitCode);
          CPPUNIT_TEST(testKilled);
          CPPUNIT_TEST(testNormalStop);
          CPPUNIT_TEST(testForcedStop);
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
          
        private:
          ProcessTest(const ProcessTest& other);
          ProcessTest& operator = (const ProcessTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_PROCESSTEST_ */
