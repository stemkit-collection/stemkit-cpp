/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_BYTESTEST_H_
#define _SK_UTIL_TEST_BYTESTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class BytesTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::BytesTest);
          CPPUNIT_TEST(testBasics);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          BytesTest();
          virtual ~BytesTest();
      
          void setUp();
          void tearDown();
          void testBasics();
      
        private:
          BytesTest(const BytesTest& other);
          BytesTest& operator = (const BytesTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_BYTESTEST_H_ */
