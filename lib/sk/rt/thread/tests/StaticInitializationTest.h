/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_TESTS_STATICINITIALIZATIONTEST_H_
#define _SK_RT_THREAD_TESTS_STATICINITIALIZATIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class StaticInitializationTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::thread::tests::StaticInitializationTest);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();

          public:
            StaticInitializationTest();
            virtual ~StaticInitializationTest();

            void setUp();
            void tearDown();
            void testBasics();

          private:
            StaticInitializationTest(const StaticInitializationTest& other);
            StaticInitializationTest& operator = (const StaticInitializationTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_STATICINITIALIZATIONTEST_H_ */
