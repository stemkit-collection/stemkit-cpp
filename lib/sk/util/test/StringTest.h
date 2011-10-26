/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_STRINGTEST_
#define _SK_UTIL_TEST_STRINGTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class StringTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::StringTest);
          CPPUNIT_TEST(testConstructFromStringWithLength);
          CPPUNIT_TEST(testConstructFromCharsWithLength);
          CPPUNIT_TEST(testConstructFromCharVectorWithLength);
          CPPUNIT_TEST(testMisc);
          CPPUNIT_TEST(testEmpty);
          CPPUNIT_TEST(testCreate);
          CPPUNIT_TEST(testSum);
          CPPUNIT_TEST(testAssignment);
          CPPUNIT_TEST(testTrim);
          CPPUNIT_TEST(testInspect);
          CPPUNIT_TEST(testStartsWith);
          CPPUNIT_TEST(testEndsWith);
          CPPUNIT_TEST(testEquals);
          CPPUNIT_TEST(testEqualsIgnoreCase);
          CPPUNIT_TEST(testSqueeze);
          CPPUNIT_TEST(testTransformations);
          CPPUNIT_TEST(testCharAt);
          CPPUNIT_TEST(testIndex);
          CPPUNIT_TEST(testSubstring);
          CPPUNIT_TEST(testContains);
          CPPUNIT_TEST(testContainsIgnoreCase);
          CPPUNIT_TEST(testStringIndex);
          CPPUNIT_TEST(testValueOf);
          CPPUNIT_TEST(testMultiply);
          CPPUNIT_TEST(testCompareOperators);
          CPPUNIT_TEST(testReverseCompareOperators);
          CPPUNIT_TEST(testSeparatorSplit);
          CPPUNIT_TEST(testWhitespaceSplit);
          CPPUNIT_TEST(testEachCharSplit);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          StringTest();
          virtual ~StringTest();
          
          void setUp();
          void tearDown();
          void testMisc();
          void testConstructFromStringWithLength();
          void testConstructFromCharsWithLength();
          void testConstructFromCharVectorWithLength();
          void testEmpty();
          void testCreate();
          void testSum();
          void testAssignment();
          void testTrim();
          void testInspect();
          void testStartsWith();
          void testEndsWith();
          void testEquals();
          void testEqualsIgnoreCase();
          void testSqueeze();
          void testTransformations();
          void testCharAt();
          void testIndex();
          void testSubstring();
          void testContains();
          void testContainsIgnoreCase();
          void testStringIndex();
          void testValueOf();
          void testMultiply();
          void testCompareOperators();
          void testReverseCompareOperators();
          void testSeparatorSplit();
          void testWhitespaceSplit();
          void testEachCharSplit();
          
        private:
          StringTest(const StringTest& other);
          StringTest& operator = (const StringTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_STRINGTEST_ */
