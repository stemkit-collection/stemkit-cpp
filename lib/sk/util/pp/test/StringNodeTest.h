/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_TEST_STRINGNODETEST_H_
#define _SK_UTIL_PP_TEST_STRINGNODETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace pp {
      namespace test {
        class StringNodeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::pp::test::StringNodeTest);
            CPPUNIT_TEST(testNone);
            CPPUNIT_TEST(testQuotedOnly);
            CPPUNIT_TEST(testQuotedThenRegular);
            CPPUNIT_TEST(testQuotedThenRegularUpto);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            StringNodeTest();
            virtual ~StringNodeTest();
        
            void setUp();
            void tearDown();
            void testNone();
            void testQuotedOnly();
            void testQuotedThenRegular();
            void testQuotedThenRegularUpto();
        
          private:
            StringNodeTest(const StringNodeTest& other);
            StringNodeTest& operator = (const StringNodeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_PP_TEST_STRINGNODETEST_H_ */
