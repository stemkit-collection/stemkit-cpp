/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_UPROOTLOCATORTEST_
#define _SK_RT_CONFIG_TEST_UPROOTLOCATORTEST_

#include "MockingTestFixture.h"

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class UprootLocatorTest
          : public MockingTestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::UprootLocatorTest);
            CPPUNIT_TEST(testOneLevel);
            CPPUNIT_TEST(testOneLevelCascading);
            CPPUNIT_TEST(testMultiLevel);
            CPPUNIT_TEST(testMultiLevelFromRoot);
            CPPUNIT_TEST(testMultiLevelCascading);
          CPPUNIT_TEST_SUITE_END();

          public:
            UprootLocatorTest();
            virtual ~UprootLocatorTest();

            void testOneLevel();
            void testOneLevelCascading();
            void testMultiLevel();
            void testMultiLevelFromRoot();
            void testMultiLevelCascading();

          private:
            UprootLocatorTest(const UprootLocatorTest& other);
            UprootLocatorTest& operator = (const UprootLocatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_UPROOTLOCATORTEST_ */
