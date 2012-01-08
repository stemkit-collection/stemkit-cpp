/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORIMPLEMENTATIONTEST_H_
#define _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORIMPLEMENTATIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace pthreads {
        namespace tests {
          class ConditionMediatorImplementationTest
            : public CppUnit::TestFixture
          {
            CPPUNIT_TEST_SUITE(sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest);
              CPPUNIT_TEST(testDefaultImplementation);
              CPPUNIT_TEST(testGenericImplementation);
              CPPUNIT_TEST(testPthreadsImplementation);
            CPPUNIT_TEST_SUITE_END();

            public:
              ConditionMediatorImplementationTest();
              virtual ~ConditionMediatorImplementationTest();

              void setUp();
              void tearDown();
              void testDefaultImplementation();
              void testGenericImplementation();
              void testPthreadsImplementation();

            private:
              ConditionMediatorImplementationTest(const ConditionMediatorImplementationTest& other);
              ConditionMediatorImplementationTest& operator = (const ConditionMediatorImplementationTest& other);
          };
        }
      }
    }
  }
}

#endif /* _SK_RT_THREAD_PTHREADS_TESTS_CONDITIONMEDIATORIMPLEMENTATIONTEST_H_ */
