/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_CLONINGHOLDERTEST_
#define _SK_UTIL_TEST_CLONINGHOLDERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class CloningHolderTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::CloningHolderTest);
          CPPUNIT_TEST(testClone);
          CPPUNIT_TEST(testCopyConstructor);
          CPPUNIT_TEST(testCopyFromAlias);
          CPPUNIT_TEST(testStringLiteral);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          CloningHolderTest();
          virtual ~CloningHolderTest();
          
          void setUp();
          void tearDown();
          void testClone();
          void testCopyConstructor();
          void testCopyFromAlias();
          void testStringLiteral();
          
        private:
          CloningHolderTest(const CloningHolderTest& other);
          CloningHolderTest& operator = (const CloningHolderTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_CLONINGHOLDERTEST_ */
