/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_COPYINGHOLDERTEST_
#define _SK_UTIL_TEST_COPYINGHOLDERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class CopyingHolderTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::CopyingHolderTest);
          CPPUNIT_TEST(testClone);
          CPPUNIT_TEST(testCopyConstructor);
          CPPUNIT_TEST(testCopyFromAlias);
          CPPUNIT_TEST(testStringLiteral);
          CPPUNIT_TEST(testAssignment);
          CPPUNIT_TEST(testAssignmentFromOther);
          CPPUNIT_TEST(testContains);
        CPPUNIT_TEST_SUITE_END();

        public:
          CopyingHolderTest();
          virtual ~CopyingHolderTest();

          void setUp();
          void tearDown();
          void testClone();
          void testCopyConstructor();
          void testCopyFromAlias();
          void testStringLiteral();
          void testAssignment();
          void testAssignmentFromOther();
          void testContains();

        private:
          CopyingHolderTest(const CopyingHolderTest& other);
          CopyingHolderTest& operator = (const CopyingHolderTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_COPYINGHOLDERTEST_ */
