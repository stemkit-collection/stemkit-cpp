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
      class ClosedChannelExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::ClosedChannelExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();

        public:
          ClosedChannelExceptionTest();
          virtual ~ClosedChannelExceptionTest();

          void setUp();
          void tearDown();
          void testThrow();

        private:
          ClosedChannelExceptionTest(const ClosedChannelExceptionTest& other);
          ClosedChannelExceptionTest& operator = (const ClosedChannelExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_EOFEXCEPTEOFNTEST_ */
