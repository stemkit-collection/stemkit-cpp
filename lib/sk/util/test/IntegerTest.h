/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_INTEGERTEST_
#define _SK_UTIL_TEST_INTEGERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class IntegerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::IntegerTest);
          CPPUNIT_TEST(testClassName);
          CPPUNIT_TEST(testStaticToString);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          IntegerTest();
          virtual ~IntegerTest();
          
          void setUp();
          void tearDown();
          void testClassName();
          void testStaticToString();
          
        private:
          IntegerTest(const IntegerTest& other);
          IntegerTest& operator = (const IntegerTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_INTEGERTEST_ */
