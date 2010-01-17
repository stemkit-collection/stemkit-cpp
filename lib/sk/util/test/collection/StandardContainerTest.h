/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_STANDARDCONTAINERTEST_
#define _SK_UTIL_TEST_STANDARDCONTAINERTEST_

#include "ListTest.h"

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class StandardContainerTest
          : public ListTest
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::StandardContainerTest);
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
            // CPPUNIT_TEST(testListInspect);
            CPPUNIT_TEST(testListAddFirst);
            CPPUNIT_TEST(testListAddLast);
            CPPUNIT_TEST(testListGetFirstLast);

            CPPUNIT_TEST(testStandardContainerCreate);
            CPPUNIT_TEST(testStandardContainerAdd);
            CPPUNIT_TEST(testStandardContainerGet);
            CPPUNIT_TEST(testStandardContainerForEach);
            CPPUNIT_TEST(testStandardContainerFind);
            CPPUNIT_TEST(testStandardContainerContains);
            CPPUNIT_TEST(testStandardContainerRemove);
            CPPUNIT_TEST(testStandardContainerSort);
            CPPUNIT_TEST(testStandardContainerInspect);
            CPPUNIT_TEST(testStandardContainerRemoveAll);
            CPPUNIT_TEST(testStandardContainerShuffle);
            CPPUNIT_TEST(testStandardContainerReverse);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            StandardContainerTest();
            virtual ~StandardContainerTest();
            
            void setUp();
            void tearDown();
            void testStandardContainerCreate();
            void testStandardContainerAdd();
            void testStandardContainerGet();
            void testStandardContainerForEach();
            void testStandardContainerFind();
            void testStandardContainerContains();
            void testStandardContainerRemove();
            void testStandardContainerSort();
            void testStandardContainerInspect();
            void testStandardContainerRemoveAll();
            void testStandardContainerShuffle();
            void testStandardContainerReverse();
            
          protected:
            virtual sk::util::List<sk::util::String>* makeStoringList();

          private:
            StandardContainerTest(const StandardContainerTest& other);
            StandardContainerTest& operator = (const StandardContainerTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_STANDARDCONTAINERTEST_ */
