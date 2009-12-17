/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_ABSTRACTLISTTEST_H_
#define _SK_UTIL_TEST_COLLECTION_ABSTRACTLISTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "CollectionTest.h"

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class AbstractListTest
          : public CollectionTest
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::AbstractListTest);
            CPPUNIT_TEST(testCollectionBasics);
            CPPUNIT_TEST(testCollectionContains);
            CPPUNIT_TEST(testCollectionContainsAll);
            CPPUNIT_TEST(testCollectionClear);
            CPPUNIT_TEST(testCollectionSelectorRemoveAll);
            CPPUNIT_TEST(testCollectionCollectionRemoveAll);
            CPPUNIT_TEST(testCollectionSelectorRetainAll);
            CPPUNIT_TEST(testCollectionCollectionRetainAll);

            CPPUNIT_TEST(testListAdd);
            CPPUNIT_TEST(testListGet);
            CPPUNIT_TEST(testListGetMutable);
            CPPUNIT_TEST(testListIndexOf);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            AbstractListTest();
            virtual ~AbstractListTest();
        
            void setUp();
            void tearDown();
        
            void testListAdd();
            void testListGet();
            void testListGetMutable();
            void testListIndexOf();

          protected:
            sk::util::Collection<sk::util::String>* makeCollection();

          private:
            AbstractListTest(const AbstractListTest& other);
            AbstractListTest& operator = (const AbstractListTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_ABSTRACTLISTTEST_H_ */
