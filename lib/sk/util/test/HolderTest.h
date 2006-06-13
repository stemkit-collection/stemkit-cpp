/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_HOLDERTEST_
#define _SK_UTIL_TEST_HOLDERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class HolderTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::HolderTest);
          CPPUNIT_TEST(testCreateWithReference);
          CPPUNIT_TEST(testCreateWithPointer);
          CPPUNIT_TEST(testCreateEmpty);
          CPPUNIT_TEST(testRemove);
          CPPUNIT_TEST(testRelease);
          CPPUNIT_TEST(testSet);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          HolderTest();
          virtual ~HolderTest();
          
          void setUp();
          void tearDown();
          void testCreateWithReference();
          void testCreateWithPointer();
          void testCreateEmpty();
          void testRemove();
          void testRelease();
          void testSet();
          
        private:
          HolderTest(const HolderTest& other);
          HolderTest& operator = (const HolderTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_HOLDERTEST_ */
