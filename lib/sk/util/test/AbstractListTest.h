/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ABSTRACTLISTTEST_
#define _SK_UTIL_TEST_ABSTRACTLISTTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class AbstractListTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::AbstractListTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AbstractListTest();
          virtual ~AbstractListTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          AbstractListTest(const AbstractListTest& other);
          AbstractListTest& operator = (const AbstractListTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_ABSTRACTLISTTEST_ */
