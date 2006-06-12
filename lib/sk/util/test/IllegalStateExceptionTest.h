/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ILLEGALSTATEEXCEPTIONTEST_
#define _SK_UTIL_TEST_ILLEGALSTATEEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class IllegalStateExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::IllegalStateExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          IllegalStateExceptionTest();
          virtual ~IllegalStateExceptionTest();
          
          void setUp();
          void tearDown();
          void testThrow();
          
        private:
          IllegalStateExceptionTest(const IllegalStateExceptionTest& other);
          IllegalStateExceptionTest& operator = (const IllegalStateExceptionTest& other);
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::IllegalStateExceptionTest);

#endif /* _SK_UTIL_TEST_ILLEGALSTATEEXCEPTIONTEST_ */
