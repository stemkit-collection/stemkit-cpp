/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_STRINGARRAYTEST_
#define _SK_UTIL_TEST_STRINGARRAYTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class StringArrayTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::StringArrayTest);
          CPPUNIT_TEST(testEmpty);
          CPPUNIT_TEST(testOne);
          CPPUNIT_TEST(testPlusString);
          CPPUNIT_TEST(testPlusOther);
          CPPUNIT_TEST(testPopulate);
          CPPUNIT_TEST(testAddString);
          CPPUNIT_TEST(testInspect);
          CPPUNIT_TEST(testParseDefault);
          CPPUNIT_TEST(testParseWithSeparator);
          CPPUNIT_TEST(testJoin);
          CPPUNIT_TEST(testLastFirst);
          CPPUNIT_TEST(testPopShift);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          StringArrayTest();
          virtual ~StringArrayTest();
          
          void setUp();
          void tearDown();
          void testEmpty();
          void testOne();
          void testPlusString();
          void testPlusOther();
          void testPopulate();
          void testAddString();
          void testInspect();
          void testParseDefault();
          void testParseWithSeparator();
          void testJoin();
          void testLastFirst();
          void testPopShift();
          
        private:
          StringArrayTest(const StringArrayTest& other);
          StringArrayTest& operator = (const StringArrayTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_STRINGARRAYTEST_ */
