/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_VECTORTEST_H_
#define _SK_UTIL_TEST_COLLECTION_VECTORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class VectorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::VectorTest);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            VectorTest();
            virtual ~VectorTest();
        
            void setUp();
            void tearDown();
            void testBasics();
        
          private:
            VectorTest(const VectorTest& other);
            VectorTest& operator = (const VectorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_VECTORTEST_H_ */
