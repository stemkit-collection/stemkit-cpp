/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_ARRAYLISTTEST_
#define _SK_UTIL_TEST_ARRAYLISTTEST_

#include "ListTest.h"

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class ArrayListTest
          : public ListTest
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::ArrayListTest);
          /*
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
          */

            CPPUNIT_TEST(testCreate);
            CPPUNIT_TEST(testAdd);
            CPPUNIT_TEST(testGet);
            CPPUNIT_TEST(testForEach);
            CPPUNIT_TEST(testFind);
            CPPUNIT_TEST(testContains);
            CPPUNIT_TEST(testRemove);
            CPPUNIT_TEST(testSort);
            CPPUNIT_TEST(testInspect);
            CPPUNIT_TEST(testRemoveAll);
            CPPUNIT_TEST(testShuffle);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            ArrayListTest();
            virtual ~ArrayListTest();
            
            void setUp();
            void tearDown();
            void testCreate();
            void testAdd();
            void testGet();
            void testForEach();
            void testFind();
            void testContains();
            void testRemove();
            void testSort();
            void testInspect();
            void testRemoveAll();
            void testShuffle();
            
          protected:
            sk::util::List<sk::util::String>* makeList();

          private:
            ArrayListTest(const ArrayListTest& other);
            ArrayListTest& operator = (const ArrayListTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_ARRAYLISTTEST_ */
