/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_CONDITIONMEDIATORENSUREGENERICTEST_H_
#define _SK_RT_THREAD_TESTS_CONDITIONMEDIATORENSUREGENERICTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class ConditionMediatorEnsureGenericTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ConditionMediatorEnsureGenericTest);
            CPPUNIT_TEST(testGenericConditionMediator);
          CPPUNIT_TEST_SUITE_END();

          public:
            ConditionMediatorEnsureGenericTest();
            virtual ~ConditionMediatorEnsureGenericTest();

            void setUp();
            void tearDown();
            void testGenericConditionMediator();

          private:
            ConditionMediatorEnsureGenericTest(const ConditionMediatorEnsureGenericTest& other);
            ConditionMediatorEnsureGenericTest& operator = (const ConditionMediatorEnsureGenericTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_CONDITIONMEDIATORENSUREGENERICTEST_H_ */
