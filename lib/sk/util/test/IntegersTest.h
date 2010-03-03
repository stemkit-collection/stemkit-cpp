/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_INTEGERSTEST_H_
#define _SK_UTIL_TEST_INTEGERSTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class IntegersTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::IntegersTest);
          CPPUNIT_TEST(testBasics);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          IntegersTest();
          virtual ~IntegersTest();
      
          void setUp();
          void tearDown();
          void testBasics();
      
        private:
          IntegersTest(const IntegersTest& other);
          IntegersTest& operator = (const IntegersTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_INTEGERSTEST_H_ */
