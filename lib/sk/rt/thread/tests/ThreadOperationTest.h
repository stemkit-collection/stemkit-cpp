/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_THREADOPERATIONTEST_H_
#define _SK_RT_THREAD_TESTS_THREADOPERATIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class ThreadOperationTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ThreadOperationTest);
            CPPUNIT_TEST(testMainThread);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ThreadOperationTest();
            virtual ~ThreadOperationTest();
        
            void setUp();
            void tearDown();
            void testMainThread();
            void testBasics();
        
          private:
            ThreadOperationTest(const ThreadOperationTest& other);
            ThreadOperationTest& operator = (const ThreadOperationTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_THREADOPERATIONTEST_H_ */
