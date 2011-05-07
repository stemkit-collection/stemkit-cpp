/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_EXCEPTIONTRACERTEST_H_
#define _SK_UTIL_TEST_EXCEPTIONTRACERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ExceptionTracerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ExceptionTracerTest);
          CPPUNIT_TEST(test_trace_produced_normally);
          CPPUNIT_TEST(test_trace_errors_in_setup);
          CPPUNIT_TEST(test_trace_errors_in_reset);
          CPPUNIT_TEST(test_trace_errors_in_produce);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          ExceptionTracerTest();
          virtual ~ExceptionTracerTest();
      
          void setUp();
          void tearDown();
          void test_trace_produced_normally();
          void test_trace_errors_in_setup();
          void test_trace_errors_in_reset();
          void test_trace_errors_in_produce();
      
        private:
          ExceptionTracerTest(const ExceptionTracerTest& other);
          ExceptionTracerTest& operator = (const ExceptionTracerTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_EXCEPTIONTRACERTEST_H_ */
