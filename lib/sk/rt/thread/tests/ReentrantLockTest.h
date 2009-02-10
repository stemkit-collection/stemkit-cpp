/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_REENTRANTLOCKTEST_H_
#define _SK_RT_THREAD_TESTS_REENTRANTLOCKTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class ReentrantLockTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ReentrantLockTest);
             CPPUNIT_TEST(testBasics);
             CPPUNIT_TEST(testLocking);
             CPPUNIT_TEST(testSynchronize);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ReentrantLockTest();
            virtual ~ReentrantLockTest();
        
            void setUp();
            void tearDown();
            void testLocking();
            void testSynchronize();
            void testBasics();
        
          private:
            ReentrantLockTest(const ReentrantLockTest& other);
            ReentrantLockTest& operator = (const ReentrantLockTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_REENTRANTLOCKTEST_H_ */
