/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_TEST_DAEMONPROCESSTEST_H_
#define _SK_SYS_TEST_DAEMONPROCESSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class DaemonProcessTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::DaemonProcessTest);
          CPPUNIT_TEST(testStartStop);
          CPPUNIT_TEST(testDestroyKillsProcess);
          CPPUNIT_TEST(testDestroyLeavesProcessWhenStartedDetached);
          CPPUNIT_TEST(testDestroyLeavesProcessWhenExplicitlyDetached);
          // CPPUNIT_TEST(testFailedCommand);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          DaemonProcessTest();
          virtual ~DaemonProcessTest();
      
          void setUp();
          void tearDown();
          void testStartStop();
          void testDestroyKillsProcess();
          void testDestroyLeavesProcessWhenStartedDetached();
          void testDestroyLeavesProcessWhenExplicitlyDetached();
          void testFailedCommand();
      
        private:
          DaemonProcessTest(const DaemonProcessTest& other);
          DaemonProcessTest& operator = (const DaemonProcessTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_DAEMONPROCESSTEST_H_ */
