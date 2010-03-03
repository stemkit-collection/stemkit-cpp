/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_STRINGSTEST_
#define _SK_UTIL_TEST_STRINGSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class StringsTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::StringsTest);
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
          CPPUNIT_TEST(testSlice);
          CPPUNIT_TEST(testMap);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          StringsTest();
          virtual ~StringsTest();
          
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
          void testSlice();
          void testMap();
          
        private:
          StringsTest(const StringsTest& other);
          StringsTest& operator = (const StringsTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_STRINGSTEST_ */
