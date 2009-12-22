/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_SHARINGHOLDERTEST_
#define _SK_UTIL_TEST_SHARINGHOLDERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class SharingHolderTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::SharingHolderTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testAssignment);
          CPPUNIT_TEST(testReplacement);
          CPPUNIT_TEST(testReplacementAfterClear);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          SharingHolderTest();
          virtual ~SharingHolderTest();
          
          void setUp();
          void tearDown();
          void testBasics();
          void testAssignment();
          void testReplacementAfterClear();
          void testReplacement();
          
        private:
          SharingHolderTest(const SharingHolderTest& other);
          SharingHolderTest& operator = (const SharingHolderTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_SHARINGHOLDERTEST_ */
