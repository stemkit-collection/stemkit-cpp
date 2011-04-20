/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_EXCEPTIONPROXYTEST_H_
#define _SK_UTIL_TEST_EXCEPTIONPROXYTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ExceptionProxyTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ExceptionProxyTest);
          CPPUNIT_TEST(test_wraps_stemkit_exception);
          CPPUNIT_TEST(test_wraps_stemkit_derived_exception);
          CPPUNIT_TEST(test_wraps_std_exception);
          CPPUNIT_TEST(test_wraps_std_string);
          CPPUNIT_TEST(test_wraps_unknown_exception);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          ExceptionProxyTest();
          virtual ~ExceptionProxyTest();
      
          void setUp();
          void tearDown();
          void test_wraps_stemkit_exception();
          void test_wraps_stemkit_derived_exception();
          void test_wraps_std_exception();
          void test_wraps_std_string();
          void test_wraps_unknown_exception();
      
        private:
          ExceptionProxyTest(const ExceptionProxyTest& other);
          ExceptionProxyTest& operator = (const ExceptionProxyTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_EXCEPTIONPROXYTEST_H_ */
