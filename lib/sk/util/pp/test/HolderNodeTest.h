/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_TEST_HOLDERNODETEST_H_
#define _SK_UTIL_PP_TEST_HOLDERNODETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace pp {
      namespace test {
        class HolderNodeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::pp::test::HolderNodeTest);
            CPPUNIT_TEST(testNone);
            CPPUNIT_TEST(testEmpty);
            CPPUNIT_TEST(testHoldPointer);
            CPPUNIT_TEST(testHoldText);
            CPPUNIT_TEST(testHoldQuotedText);
            CPPUNIT_TEST(testHoldHolder);
          CPPUNIT_TEST_SUITE_END();

          public:
            HolderNodeTest();
            virtual ~HolderNodeTest();

            void setUp();
            void tearDown();
            void testNone();
            void testEmpty();
            void testHoldPointer();
            void testHoldText();
            void testHoldQuotedText();
            void testHoldHolder();

          private:
            HolderNodeTest(const HolderNodeTest& other);
            HolderNodeTest& operator = (const HolderNodeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_PP_TEST_HOLDERNODETEST_H_ */
