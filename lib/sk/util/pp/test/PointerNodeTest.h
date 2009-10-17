/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_TEST_POINTERNODETEST_H_
#define _SK_UTIL_PP_TEST_POINTERNODETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace pp {
      namespace test {
        class PointerNodeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::pp::test::PointerNodeTest);
            CPPUNIT_TEST(testNone);
            CPPUNIT_TEST(testNull);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            PointerNodeTest();
            virtual ~PointerNodeTest();
        
            void setUp();
            void tearDown();
            void testNone();
            void testNull();
        
          private:
            PointerNodeTest(const PointerNodeTest& other);
            PointerNodeTest& operator = (const PointerNodeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_PP_TEST_POINTERNODETEST_H_ */
