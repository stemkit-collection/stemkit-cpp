/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_TESTS_ENVIRONMENTTEST_H_
#define _SK_RT_TESTS_ENVIRONMENTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class EnvironmentTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::EnvironmentTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testSerializeEmpty);
          CPPUNIT_TEST(testSerializeContent);
        CPPUNIT_TEST_SUITE_END();

        public:
          EnvironmentTest();
          virtual ~EnvironmentTest();

          void setUp();
          void tearDown();
          void testBasics();
          void testSerializeEmpty();
          void testSerializeContent();

        private:
          EnvironmentTest(const EnvironmentTest& other);
          EnvironmentTest& operator = (const EnvironmentTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_ENVIRONMENTTEST_H_ */
