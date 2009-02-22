/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_WIN32_TESTS_CRITICALSECTIONTEST_H_
#define _SK_RT_THREAD_WIN32_TESTS_CRITICALSECTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace win32 {
        namespace tests {
          class CriticalSectionTest
            : public CppUnit::TestFixture
          {
            CPPUNIT_TEST_SUITE(sk::rt::thread::win32::tests::CriticalSectionTest);
              CPPUNIT_TEST(testBasics);
            CPPUNIT_TEST_SUITE_END();
          
            public:
              CriticalSectionTest();
              virtual ~CriticalSectionTest();
          
              void setUp();
              void tearDown();
              void testBasics();
          
            private:
              CriticalSectionTest(const CriticalSectionTest& other);
              CriticalSectionTest& operator = (const CriticalSectionTest& other);
          };
        }
      }
    }
  }
}

#endif /* _SK_RT_THREAD_WIN32_TESTS_CRITICALSECTIONTEST_H_ */
