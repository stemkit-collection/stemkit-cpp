/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_EOFEXCEPTEOFNTEST_
#define _SK_UTIL_TEST_EOFEXCEPTEOFNTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class EOFExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::EOFExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          EOFExceptionTest();
          virtual ~EOFExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          EOFExceptionTest(const EOFExceptionTest& other);
          EOFExceptionTest& operator = (const EOFExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_EOFEXCEPTEOFNTEST_ */
