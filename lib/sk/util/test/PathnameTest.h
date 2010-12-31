/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_PATHNAMETEST_
#define _SK_UTIL_TEST_PATHNAMETEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class PathnameTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::PathnameTest);
          CPPUNIT_TEST(testEmpty);
          CPPUNIT_TEST(testJoinOther);
          CPPUNIT_TEST(testJoinString);
          CPPUNIT_TEST(testPlus);
          CPPUNIT_TEST(testExtension);
          CPPUNIT_TEST(testIsAbsolute);
          // CPPUNIT_TEST(testIsTerminal);
          CPPUNIT_TEST(testDirname);
          CPPUNIT_TEST(testBasename);
          CPPUNIT_TEST(testLocation);
          CPPUNIT_TEST(testWindowsResourcePath);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          PathnameTest();
          virtual ~PathnameTest();
          
          void setUp();
          void tearDown();
          void testEmpty();
          void testJoinOther();
          void testJoinString();
          void testPlus();
          void testExtension();
          void testIsAbsolute();
          void testIsTerminal();
          void testDirname();
          void testBasename();
          void testLocation();
          void testWindowsResourcePath();
          
        private:
          PathnameTest(const PathnameTest& other);
          PathnameTest& operator = (const PathnameTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_PATHNAMETEST_ */
