/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_LISTTEST_H_
#define _SK_UTIL_TEST_COLLECTION_LISTTEST_H_

#include "CollectionTest.h"
#include <sk/util/List.h>

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class ListTest
          : public CollectionTest
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::ListTest);
            CPPUNIT_TEST(testCollectionBasics);
            CPPUNIT_TEST(testCollectionGet);
            CPPUNIT_TEST(testCollectionGetMutable);
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
            CPPUNIT_TEST(testListRemove);
            CPPUNIT_TEST(testListSet);
            CPPUNIT_TEST(testListInspect);

            CPPUNIT_TEST(testListAddFirst);
            CPPUNIT_TEST(testListAddLast);
            CPPUNIT_TEST(testListGetFirstLast);
            CPPUNIT_TEST(testListGetMutableFirstLast);
            CPPUNIT_TEST(testListRemoveFirstLast);
            CPPUNIT_TEST(testListCutoffFirstLast);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ListTest();
        
            void testListAdd();
            void testListGet();
            void testListGetMutable();
            void testListIndexOf();
            void testListRemove();
            void testListSet();
            void testListInspect();

            void testListAddFirst();
            void testListAddLast();
            void testListGetFirstLast();
            void testListGetMutableFirstLast();
            void testListRemoveFirstLast();
            void testListCutoffFirstLast();

          protected:
            sk::util::Collection<sk::util::String>* makeCopyingCollection();
            virtual sk::util::List<sk::util::String>* makeCopyingList();

            typedef sk::util::List<sk::util::String> List;

          private:
            ListTest(const ListTest& other);
            ListTest& operator = (const ListTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_LISTTEST_H_ */
