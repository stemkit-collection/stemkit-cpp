/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_TESTS_RECURSIVEMUTEXTEST_H_
#define _SK_RT_THREAD_PTHREADS_TESTS_RECURSIVEMUTEXTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        namespace tests {
          class RecursiveMutexTest
            : public CppUnit::TestFixture
          {
            CPPUNIT_TEST_SUITE(sk::rt::thread::pthreads::tests::RecursiveMutexTest);
              CPPUNIT_TEST(testUnlockFailsOnNonLocked);
              CPPUNIT_TEST(testLockUnlock);
              CPPUNIT_TEST(testTryLock);
            CPPUNIT_TEST_SUITE_END();
          
            public:
              RecursiveMutexTest();
              virtual ~RecursiveMutexTest();
          
              void setUp();
              void tearDown();
              void testUnlockFailsOnNonLocked();
              void testLockUnlock();
              void testTryLock();
          
            private:
              RecursiveMutexTest(const RecursiveMutexTest& other);
              RecursiveMutexTest& operator = (const RecursiveMutexTest& other);
          };
        }
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_TESTS_RECURSIVEMUTEXTEST_H_ */
