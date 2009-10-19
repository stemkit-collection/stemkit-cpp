/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_PP_TEST_STRUCTNODETEST_H_
#define _SK_UTIL_PP_TEST_STRUCTNODETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace pp {
      namespace test {
        class StructNodeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::pp::test::StructNodeTest);
            CPPUNIT_TEST(testEmpty);
            CPPUNIT_TEST(testOne);
            CPPUNIT_TEST(testMany);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            StructNodeTest();
            virtual ~StructNodeTest();
        
            void setUp();
            void tearDown();
            void testEmpty();
            void testOne();
            void testMany();
        
          private:
            StructNodeTest(const StructNodeTest& other);
            StructNodeTest& operator = (const StructNodeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_PP_TEST_STRUCTNODETEST_H_ */
