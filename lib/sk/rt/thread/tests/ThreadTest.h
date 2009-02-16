/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_TESTS_THREADTEST_H_
#define _SK_RT_THREAD_TESTS_THREADTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class ThreadTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ThreadTest);
            CPPUNIT_TEST(testCreateDefault);
            CPPUNIT_TEST(testMainThread);
            CPPUNIT_TEST(testDataGeneration);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ThreadTest();
            virtual ~ThreadTest();
        
            void setUp();
            void tearDown();
            void testCreateDefault();
            void testMainThread();
            void testDataGeneration();
        
          private:
            ThreadTest(const ThreadTest& other);
            ThreadTest& operator = (const ThreadTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_THREADTEST_H_ */
