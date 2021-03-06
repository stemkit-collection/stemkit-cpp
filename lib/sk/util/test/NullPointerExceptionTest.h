/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_NULLPOINTEREXCEPTIONTEST_
#define _SK_UTIL_TEST_NULLPOINTEREXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class NullPointerExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::NullPointerExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          NullPointerExceptionTest();
          virtual ~NullPointerExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          NullPointerExceptionTest(const NullPointerExceptionTest& other);
          NullPointerExceptionTest& operator = (const NullPointerExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_NULLPOINTEREXCEPTIONTEST_ */
