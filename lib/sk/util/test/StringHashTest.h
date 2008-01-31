/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_STRINGHASHTEST_
#define _SK_UTIL_TEST_STRINGHASHTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class StringHashTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::StringHashTest);
          CPPUNIT_TEST(testBasics);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          StringHashTest();
          virtual ~StringHashTest();
          
          void setUp();
          void testBasics();
          void tearDown();
          
        private:
          StringHashTest(const StringHashTest& other);
          StringHashTest& operator = (const StringHashTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_STRINGHASHTEST_ */
