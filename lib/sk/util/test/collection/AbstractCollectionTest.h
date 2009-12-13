/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_ABSTRACTCOLLECTIONTEST_H_
#define _SK_UTIL_TEST_COLLECTION_ABSTRACTCOLLECTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class AbstractCollectionTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::AbstractCollectionTest);
            CPPUNIT_TEST(testBasics);
            CPPUNIT_TEST(testContains);
            CPPUNIT_TEST(testContainsAll);
            CPPUNIT_TEST(testClear);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            AbstractCollectionTest();
            virtual ~AbstractCollectionTest();
        
            void setUp();
            void tearDown();
            void testBasics();
            void testContains();
            void testContainsAll();
            void testClear();
        
          private:
            AbstractCollectionTest(const AbstractCollectionTest& other);
            AbstractCollectionTest& operator = (const AbstractCollectionTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_ABSTRACTCOLLECTIONTEST_H_ */
