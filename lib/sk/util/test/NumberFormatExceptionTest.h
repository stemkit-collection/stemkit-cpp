/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_NUMBERFORMATEXCEPTIONTEST_
#define _SK_UTIL_TEST_NUMBERFORMATEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class NumberFormatExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::NumberFormatExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          NumberFormatExceptionTest();
          virtual ~NumberFormatExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          NumberFormatExceptionTest(const NumberFormatExceptionTest& other);
          NumberFormatExceptionTest& operator = (const NumberFormatExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_NUMBERFORMATEXCEPTIONTEST_ */
