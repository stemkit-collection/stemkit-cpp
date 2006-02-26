/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_CLASSTEST_
#define _SK_UTIL_TEST_CLASSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ClassTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ClassTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ClassTest();
          virtual ~ClassTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          ClassTest(const ClassTest& other);
          ClassTest& operator = (const ClassTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_CLASSTEST_ */
