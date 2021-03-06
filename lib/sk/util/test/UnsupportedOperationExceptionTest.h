/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_UNSUPPORTEDOPERATIONEXCEPTIONTEST_
#define _SK_UTIL_TEST_UNSUPPORTEDOPERATIONEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class UnsupportedOperationExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::UnsupportedOperationExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          UnsupportedOperationExceptionTest();
          virtual ~UnsupportedOperationExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          UnsupportedOperationExceptionTest(const UnsupportedOperationExceptionTest& other);
          UnsupportedOperationExceptionTest& operator = (const UnsupportedOperationExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_UNSUPPORTEDOPERATIONEXCEPTIONTEST_ */
