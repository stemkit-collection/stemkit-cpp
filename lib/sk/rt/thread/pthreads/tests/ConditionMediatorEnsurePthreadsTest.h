/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORENSUREPTHREADSTEST_H_
#define _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORENSUREPTHREADSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        namespace tests {
          class ConditionMediatorEnsurePthreadsTest
            : public CppUnit::TestFixture
          {
            CPPUNIT_TEST_SUITE(sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest);
              CPPUNIT_TEST(testPthreadsConditionMediator);
            CPPUNIT_TEST_SUITE_END();

            public:
              ConditionMediatorEnsurePthreadsTest();
              virtual ~ConditionMediatorEnsurePthreadsTest();

              void setUp();
              void tearDown();
              void testPthreadsConditionMediator();

            private:
              ConditionMediatorEnsurePthreadsTest(const ConditionMediatorEnsurePthreadsTest& other);
              ConditionMediatorEnsurePthreadsTest& operator = (const ConditionMediatorEnsurePthreadsTest& other);
          };
        }
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORENSUREPTHREADSTEST_H_ */
