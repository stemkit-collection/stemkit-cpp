/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_MUTEXTEST_H_
#define _SK_RT_THREAD_TESTS_MUTEXTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class MutexTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::MutexTest);
            CPPUNIT_TEST(testLocking);
            CPPUNIT_TEST(testSynchronize);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            MutexTest();
            virtual ~MutexTest();
        
            void setUp();
            void tearDown();
            void testLocking();
            void testSynchronize();
        
          private:
            MutexTest(const MutexTest& other);
            MutexTest& operator = (const MutexTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_MUTEXTEST_H_ */
