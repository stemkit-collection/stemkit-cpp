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

          protected:
            sk::util::Collection<sk::util::String>* makeCollection();
            virtual sk::util::List<sk::util::String>* makeList();

          private:
            typedef sk::util::List<sk::util::String> List;

            ListTest(const ListTest& other);
            ListTest& operator = (const ListTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_LISTTEST_H_ */
