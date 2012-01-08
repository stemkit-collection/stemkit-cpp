/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_INTERRUPTEDEXCEPTIONTEST_
#define _SK_UTIL_TEST_INTERRUPTEDEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class InterruptedExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::InterruptedExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          InterruptedExceptionTest();
          virtual ~InterruptedExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          InterruptedExceptionTest(const InterruptedExceptionTest& other);
          InterruptedExceptionTest& operator = (const InterruptedExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_INTERRUPTEDEXCEPTIONTEST_ */
