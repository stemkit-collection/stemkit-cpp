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

#include "CollectionTest.h"

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class AbstractCollectionTest
          : public CollectionTest
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::AbstractCollectionTest);
            CPPUNIT_TEST(testCollectionBasics);
            CPPUNIT_TEST(testCollectionGet);
            // CPPUNIT_TEST(testCollectionGetMutable);
            CPPUNIT_TEST(testCollectionContains);
            CPPUNIT_TEST(testCollectionContainsAll);
            CPPUNIT_TEST(testCollectionClear);
            CPPUNIT_TEST(testCollectionSelectorRemoveAll);
            CPPUNIT_TEST(testCollectionCollectionRemoveAll);
            CPPUNIT_TEST(testCollectionSelectorRetainAll);
            CPPUNIT_TEST(testCollectionCollectionRetainAll);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            AbstractCollectionTest();
            virtual ~AbstractCollectionTest();
        
          protected:
            sk::util::Collection<sk::util::String>* makeCopyingCollection();

          private:
            AbstractCollectionTest(const AbstractCollectionTest& other);
            AbstractCollectionTest& operator = (const AbstractCollectionTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_ABSTRACTCOLLECTIONTEST_H_ */
