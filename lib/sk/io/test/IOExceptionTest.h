/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_IOEXCEPTIONTEST_
#define _SK_UTIL_TEST_IOEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class IOExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::IOExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          IOExceptionTest();
          virtual ~IOExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          IOExceptionTest(const IOExceptionTest& other);
          IOExceptionTest& operator = (const IOExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_IOEXCEPTIONTEST_ */
