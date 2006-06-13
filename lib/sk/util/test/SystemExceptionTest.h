/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_SYSTEMEXCEPTIONTEST_
#define _SK_UTIL_TEST_SYSTEMEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class SystemExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::SystemExceptionTest);
          CPPUNIT_TEST(testThrow);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          SystemExceptionTest();
          virtual ~SystemExceptionTest();
          
          void setUp();
          void tearDown();
          void testThrow();
          
        private:
          SystemExceptionTest(const SystemExceptionTest& other);
          SystemExceptionTest& operator = (const SystemExceptionTest& other);
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::SystemExceptionTest);

#endif /* _SK_UTIL_TEST_SYSTEMEXCEPTIONTEST_ */
