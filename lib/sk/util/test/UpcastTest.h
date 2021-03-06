/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_UPCASTTEST_H_
#define _SK_UTIL_TEST_UPCASTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class UpcastTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::UpcastTest);
          CPPUNIT_TEST(testFailingNonConstUpcastFromObject);
          CPPUNIT_TEST(testFailingConstUpcastFromObject);
        CPPUNIT_TEST_SUITE_END();

        public:
          UpcastTest();
          virtual ~UpcastTest();

          void setUp();
          void tearDown();
          void testFailingNonConstUpcastFromObject();
          void testFailingConstUpcastFromObject();

        private:
          UpcastTest(const UpcastTest& other);
          UpcastTest& operator = (const UpcastTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_UPCASTTEST_H_ */
