/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_SPOTLOCATORTEST_
#define _SK_RT_CONFIG_TEST_SPOTLOCATORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class SpotLocatorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::SpotLocatorTest);
            CPPUNIT_TEST(testStandAlone);
            CPPUNIT_TEST(testCascading);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            SpotLocatorTest();
            virtual ~SpotLocatorTest();
            
            void setUp();
            void tearDown();
            void testStandAlone();
            void testCascading();
            
          private:
            SpotLocatorTest(const SpotLocatorTest& other);
            SpotLocatorTest& operator = (const SpotLocatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_SPOTLOCATORTEST_ */
