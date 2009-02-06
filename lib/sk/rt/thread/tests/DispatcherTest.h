/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_DISPATCHERTEST_H_
#define _SK_RT_THREAD_TESTS_DISPATCHERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class DispatcherTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::DispatcherTest);
            CPPUNIT_TEST(testSequence);
            CPPUNIT_TEST(testMainInstance);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            DispatcherTest();
            virtual ~DispatcherTest();
        
            void setUp();
            void tearDown();
            void testSequence();
            void testMainInstance();
        
          private:
            DispatcherTest(const DispatcherTest& other);
            DispatcherTest& operator = (const DispatcherTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_DISPATCHERTEST_H_ */
