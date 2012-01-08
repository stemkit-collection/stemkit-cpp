/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_EXCEPTIONTEST_
#define _SK_UTIL_TEST_EXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ExceptionTest);
          CPPUNIT_TEST(testThrow);
          CPPUNIT_TEST(testStandard);
        CPPUNIT_TEST_SUITE_END();

        public:
          ExceptionTest();
          virtual ~ExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();
          void testStandard();

        private:
          ExceptionTest(const ExceptionTest& other);
          ExceptionTest& operator = (const ExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_EXCEPTIONTEST_ */
