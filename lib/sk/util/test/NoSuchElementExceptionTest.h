/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_NOSUCHELEMENTEXCEPTIONTEST_
#define _SK_UTIL_TEST_NOSUCHELEMENTEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class NoSuchElementExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::NoSuchElementExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          NoSuchElementExceptionTest();
          virtual ~NoSuchElementExceptionTest();
          
          void setUp();
          void tearDown();
          void testThrow();
          
        private:
          NoSuchElementExceptionTest(const NoSuchElementExceptionTest& other);
          NoSuchElementExceptionTest& operator = (const NoSuchElementExceptionTest& other);
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::NoSuchElementExceptionTest);

#endif /* _SK_UTIL_TEST_NOSUCHELEMENTEXCEPTIONTEST_ */
