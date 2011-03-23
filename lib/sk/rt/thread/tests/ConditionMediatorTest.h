/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_CONDITIONMEDIATORTEST_H_
#define _SK_RT_THREAD_TESTS_CONDITIONMEDIATORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class ConditionMediatorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ConditionMediatorTest);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ConditionMediatorTest();
            virtual ~ConditionMediatorTest();
        
            void setUp();
            void tearDown();
            void testBasics();
        
          private:
            ConditionMediatorTest(const ConditionMediatorTest& other);
            ConditionMediatorTest& operator = (const ConditionMediatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_CONDITIONMEDIATORTEST_H_ */
