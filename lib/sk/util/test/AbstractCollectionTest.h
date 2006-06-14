/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ABSTRACTCOLLECTIONTEST_
#define _SK_UTIL_TEST_ABSTRACTCOLLECTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class AbstractCollectionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::AbstractCollectionTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AbstractCollectionTest();
          virtual ~AbstractCollectionTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          AbstractCollectionTest(const AbstractCollectionTest& other);
          AbstractCollectionTest& operator = (const AbstractCollectionTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_ABSTRACTCOLLECTIONTEST_ */
