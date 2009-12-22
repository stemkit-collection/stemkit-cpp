/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ALIASINGHOLDERTEST_
#define _SK_UTIL_TEST_ALIASINGHOLDERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class AliasingHolderTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::AliasingHolderTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testAssignment);
          CPPUNIT_TEST(testAssignmentFromOther);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AliasingHolderTest();
          virtual ~AliasingHolderTest();
          
          void setUp();
          void tearDown();
          void testBasics();
          void testAssignment();
          void testAssignmentFromOther();
          
        private:
          AliasingHolderTest(const AliasingHolderTest& other);
          AliasingHolderTest& operator = (const AliasingHolderTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_ALIASINGHOLDERTEST_ */
