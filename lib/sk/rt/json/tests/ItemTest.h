/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_TESTS_ITEMTEST_H_
#define _SK_RT_JSON_TESTS_ITEMTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace json {
      namespace tests {
        class ItemTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::json::tests::ItemTest);
            CPPUNIT_TEST(test_raises_exception_on_non_present);
            CPPUNIT_TEST(test_succeeds_on_present_attribute);
            CPPUNIT_TEST(test_bad_convert_raises_argument_error);
            CPPUNIT_TEST(test_can_be_copied);
          CPPUNIT_TEST_SUITE_END();

          public:
            ItemTest();
            virtual ~ItemTest();

            void setUp();
            void tearDown();
            void test_raises_exception_on_non_present();
            void test_succeeds_on_present_attribute();
            void test_bad_convert_raises_argument_error();
            void test_can_be_copied();

          private:
            ItemTest(const ItemTest& other);
            ItemTest& operator = (const ItemTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_JSON_TESTS_ITEMTEST_H_ */
