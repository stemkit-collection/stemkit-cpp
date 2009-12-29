/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_COLLECTIONTEST_H_
#define _SK_UTIL_TEST_COLLECTION_COLLECTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Collection.h>
#include <sk/util/Object.h>

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class CollectionTest
           : public CppUnit::TestFixture,
             public virtual sk::util::Object
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::CollectionTest);
            CPPUNIT_TEST(testCollectionBasics);
            CPPUNIT_TEST(testCollectionContains);
            CPPUNIT_TEST(testCollectionContainsAll);
            CPPUNIT_TEST(testCollectionClear);
            CPPUNIT_TEST(testCollectionSelectorRemoveAll);
            CPPUNIT_TEST(testCollectionCollectionRemoveAll);
            CPPUNIT_TEST(testCollectionSelectorRetainAll);
            CPPUNIT_TEST(testCollectionCollectionRetainAll);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            CollectionTest();

            void testCollectionBasics();
            void testCollectionContains();
            void testCollectionContainsAll();
            void testCollectionClear();
            void testCollectionSelectorRemoveAll();
            void testCollectionCollectionRemoveAll();
            void testCollectionSelectorRetainAll();
            void testCollectionCollectionRetainAll();

          protected:
            virtual sk::util::Collection<sk::util::String>* makeCopyingCollection();
        
          private:
            typedef sk::util::Collection<sk::util::String> Collection;

            CollectionTest(const CollectionTest& other);
            CollectionTest& operator = (const CollectionTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_COLLECTIONTEST_H_ */
