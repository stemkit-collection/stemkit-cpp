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
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    class Lock;

    namespace thread {
      class Condition;

      namespace tests {
        class ConditionMediatorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::ConditionMediatorTest);
            CPPUNIT_TEST(testSynchronizeLocksAndUnlocks);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ConditionMediatorTest();
            virtual ~ConditionMediatorTest();
        
            void setUp();
            void tearDown();
            void testSynchronizeLocksAndUnlocks();

            void ensureLocked(sk::rt::thread::Condition& condition);
        
          private:
            ConditionMediatorTest(const ConditionMediatorTest& other);
            ConditionMediatorTest& operator = (const ConditionMediatorTest& other);

            sk::util::Holder<sk::rt::Lock> _lockHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_CONDITIONMEDIATORTEST_H_ */
