/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ARRAYLISTTEST_
#define _SK_UTIL_TEST_ARRAYLISTTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ArrayListTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ArrayListTest);
          CPPUNIT_TEST(testCreate);
          CPPUNIT_TEST(testAdd);
          CPPUNIT_TEST(testForEach);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ArrayListTest();
          virtual ~ArrayListTest();
          
          void setUp();
          void tearDown();
          void testCreate();
          void testAdd();
          void testForEach();
          
        private:
          ArrayListTest(const ArrayListTest& other);
          ArrayListTest& operator = (const ArrayListTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_ARRAYLISTTEST_ */
