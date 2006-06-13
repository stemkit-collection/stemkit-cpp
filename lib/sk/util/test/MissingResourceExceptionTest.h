/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_MISSINGRESOURCEEXCEPTIONTEST_
#define _SK_UTIL_TEST_MISSINGRESOURCEEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class MissingResourceExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::MissingResourceExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          MissingResourceExceptionTest();
          virtual ~MissingResourceExceptionTest();
          
          void setUp();
          void tearDown();
          void testThrow();
          
        private:
          MissingResourceExceptionTest(const MissingResourceExceptionTest& other);
          MissingResourceExceptionTest& operator = (const MissingResourceExceptionTest& other);
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::MissingResourceExceptionTest);

#endif /* _SK_UTIL_TEST_MISSINGRESOURCEEXCEPTIONTEST_ */
