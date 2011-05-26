/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_JSON_TESTS_INTITEMTEST_H_
#define _SK_RT_JSON_TESTS_INTITEMTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace json {
      namespace tests {
        class IntItemTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::json::tests::IntItemTest);
            CPPUNIT_TEST(test_raises_exception_on_non_present);
            CPPUNIT_TEST(test_succeeds_on_present_attribute);
            CPPUNIT_TEST(test_bad_convert_raises_argument_error);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            IntItemTest();
            virtual ~IntItemTest();
        
            void setUp();
            void tearDown();
            void test_raises_exception_on_non_present();
            void test_succeeds_on_present_attribute();
            void test_bad_convert_raises_argument_error();
        
          private:
            IntItemTest(const IntItemTest& other);
            IntItemTest& operator = (const IntItemTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_JSON_TESTS_INTITEMTEST_H_ */
