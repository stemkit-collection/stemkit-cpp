/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_TESTS_MUTEXTEST_H_
#define _SK_RT_THREAD_PTHREADS_TESTS_MUTEXTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        namespace tests {
          class MutexTest
            : public CppUnit::TestFixture
          {
            CPPUNIT_TEST_SUITE(sk::rt::thread::pthreads::tests::MutexTest);
              CPPUNIT_TEST(testUnlockFailsOnNonLocked);
              CPPUNIT_TEST(testLockUnlock);
              CPPUNIT_TEST(testTryLock);
            CPPUNIT_TEST_SUITE_END();
          
            public:
              MutexTest();
              virtual ~MutexTest();
          
              void setUp();
              void tearDown();
              void testUnlockFailsOnNonLocked();
              void testLockUnlock();
              void testTryLock();
          
            private:
              MutexTest(const MutexTest& other);
              MutexTest& operator = (const MutexTest& other);
          };
        }
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_TESTS_MUTEXTEST_H_ */
