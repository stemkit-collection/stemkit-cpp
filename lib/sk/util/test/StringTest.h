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
          CPPUNIT_TEST(testCreateEmpty);
          CPPUNIT_TEST(testCreateFromBuffer);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          StringTest();
          virtual ~StringTest();
          
          void setUp();
          void tearDown();
          void testCreateEmpty();
          void testCreateFromBuffer();
          
        private:
          StringTest(const StringTest& other);
          StringTest& operator = (const StringTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_STRINGTEST_ */
