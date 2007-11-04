/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_LOCATORTEST_
#define _SK_RT_CONFIG_TEST_LOCATORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class LocatorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::LocatorTest);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            LocatorTest();
            virtual ~LocatorTest();
            
            void setUp();
            void tearDown();
            void testBasics();
            
          private:
            LocatorTest(const LocatorTest& other);
            LocatorTest& operator = (const LocatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_LOCATORTEST_ */
