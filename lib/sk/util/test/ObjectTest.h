/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_OBJECTTEST_
#define _SK_UTIL_TEST_OBJECTTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ObjectTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ObjectTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ObjectTest();
          virtual ~ObjectTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          ObjectTest(const ObjectTest& other);
          ObjectTest& operator = (const ObjectTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_OBJECTTEST_ */
