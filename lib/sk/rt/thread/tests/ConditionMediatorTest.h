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
            CPPUNIT_TEST(test_default_blocking_but_can_be_changed);
            CPPUNIT_TEST(test_blocking_locks_invokes_and_unlocks);
            CPPUNIT_TEST(test_non_blocking_locks_when_available_and_fails_otherwise);
            CPPUNIT_TEST(test_blocking_waits_until_unlocked_then_invokes);
            CPPUNIT_TEST(test_condition_wait_times_out);
            CPPUNIT_TEST(test_condition_wait_succeeds_on_announce);
            CPPUNIT_TEST(test_multi_channel_conditions);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ConditionMediatorTest();
            virtual ~ConditionMediatorTest();
        
            void setUp();
            void tearDown();
            void test_default_blocking_but_can_be_changed();
            void test_blocking_locks_invokes_and_unlocks();
            void test_non_blocking_locks_when_available_and_fails_otherwise();
            void test_blocking_waits_until_unlocked_then_invokes();
            void test_condition_wait_times_out();
            void test_condition_wait_succeeds_on_announce();
            void test_multi_channel_conditions();

            void ensureLocked(sk::rt::thread::Condition& condition, bool& indicator);
            void announceCondition(sk::rt::thread::Condition& condition, int channel);
        
          private:
            ConditionMediatorTest(const ConditionMediatorTest& other);
            ConditionMediatorTest& operator = (const ConditionMediatorTest& other);

            sk::rt::Lock& mutex();

            sk::util::Holder<sk::rt::Lock> _mutexHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_CONDITIONMEDIATORTEST_H_ */
