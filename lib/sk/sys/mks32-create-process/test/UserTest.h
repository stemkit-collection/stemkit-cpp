/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_USERTEST_
#define _SK_SYS_TEST_USERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class UserTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::UserTest);
          CPPUNIT_TEST(testFind);
          CPPUNIT_TEST(testAuthenticate);
        CPPUNIT_TEST_SUITE_END();

        public:
          UserTest();
          virtual ~UserTest();

          void setUp();
          void tearDown();
          void testFind();
          void testAuthenticate();

        private:
          UserTest(const UserTest& other);
          UserTest& operator = (const UserTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_USERTEST_ */
