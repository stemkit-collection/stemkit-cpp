/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_HOMELOCATORTEST_
#define _SK_RT_CONFIG_TEST_HOMELOCATORTEST_

#include "MockingTestFixture.h"

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class HomeLocatorTest
          : public MockingTestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::HomeLocatorTest);
            CPPUNIT_TEST(testStandAlone);
          CPPUNIT_TEST_SUITE_END();

          public:
            HomeLocatorTest();
            virtual ~HomeLocatorTest();

            void testStandAlone();

          private:
            HomeLocatorTest(const HomeLocatorTest& other);
            HomeLocatorTest& operator = (const HomeLocatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_HOMELOCATORTEST_ */
