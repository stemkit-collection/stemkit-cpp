/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_TESTS_ACTIONSTEST_H_
#define _SK_RT_TESTS_ACTIONSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class ActionsTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::ActionsTest);
          CPPUNIT_TEST(test_set_reverse_and_no_actions_no_problems);
          CPPUNIT_TEST(test_non_problem_actions_work_in_direct_order);
          CPPUNIT_TEST(test_non_problem_actions_work_in_reverse_order);
          CPPUNIT_TEST(test_non_problem_actions_work_out_of_scope_without_perform);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          ActionsTest();
          virtual ~ActionsTest();
      
          void setUp();
          void tearDown();
          void test_set_reverse_and_no_actions_no_problems();
          void test_non_problem_actions_work_in_direct_order();
          void test_non_problem_actions_work_in_reverse_order();
          void test_non_problem_actions_work_out_of_scope_without_perform();
      
        private:
          ActionsTest(const ActionsTest& other);
          ActionsTest& operator = (const ActionsTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_ACTIONSTEST_H_ */
