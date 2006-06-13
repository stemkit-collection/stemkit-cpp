/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_INDEXOUTOFBOUNDSEXCEPTIONTEST_
#define _SK_UTIL_TEST_INDEXOUTOFBOUNDSEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class IndexOutOfBoundsExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::IndexOutOfBoundsExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          IndexOutOfBoundsExceptionTest();
          virtual ~IndexOutOfBoundsExceptionTest();
          
          void setUp();
          void tearDown();
          void testThrow();
          
        private:
          IndexOutOfBoundsExceptionTest(const IndexOutOfBoundsExceptionTest& other);
          IndexOutOfBoundsExceptionTest& operator = (const IndexOutOfBoundsExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_INDEXOUTOFBOUNDSEXCEPTIONTEST_ */
