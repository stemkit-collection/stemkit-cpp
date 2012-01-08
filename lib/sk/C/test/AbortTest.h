/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_TEST_ABORTTEST_H_
#define _SK_C_TEST_ABORTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace C {
    namespace test {
      class AbortTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::C::test::AbortTest);
          CPPUNIT_TEST(testAbortWrapper);
          CPPUNIT_TEST(testAbortsOnNullHandle);
          CPPUNIT_TEST(testAbortsOnBadBuffer);
          CPPUNIT_TEST(testCanContinueAfterClear);
          CPPUNIT_TEST(testAbortsOnNextCallWhenNotCleared);
        CPPUNIT_TEST_SUITE_END();

        public:
          AbortTest();
          virtual ~AbortTest();

          void setUp();
          void tearDown();
          void testAbortWrapper();
          void testAbortsOnNullHandle();
          void testAbortsOnBadBuffer();
          void testCanContinueAfterClear();
          void testAbortsOnNextCallWhenNotCleared();

        private:
          AbortTest(const AbortTest& other);
          AbortTest& operator = (const AbortTest& other);
      };
    }
  }
}

#endif /* _SK_C_TEST_ABORTTEST_H_ */
