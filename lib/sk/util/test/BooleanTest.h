/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_BOOLEANTEST_
#define _SK_UTIL_TEST_BOOLEANTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class BooleanTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::BooleanTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testConstants);
          CPPUNIT_TEST(testParse);
          CPPUNIT_TEST(testValueOf);
          CPPUNIT_TEST(testToString);
          CPPUNIT_TEST(testStreamOutput);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          BooleanTest();
          virtual ~BooleanTest();
          
          void setUp();
          void tearDown();
          void testBasics();
          void testConstants();
          void testParse();
          void testValueOf();
          void testToString();
          void testStreamOutput();
          
        private:
          BooleanTest(const BooleanTest& other);
          BooleanTest& operator = (const BooleanTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_BOOLEANTEST_ */
