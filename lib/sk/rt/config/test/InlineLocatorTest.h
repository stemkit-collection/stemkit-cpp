/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_INLINELOCATORTEST_H_
#define _SK_RT_CONFIG_TEST_INLINELOCATORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class InlineLocatorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::InlineLocatorTest);
            CPPUNIT_TEST(testStandAlone);
          CPPUNIT_TEST_SUITE_END();

          public:
            InlineLocatorTest();
            virtual ~InlineLocatorTest();

            void testStandAlone();

          private:
            InlineLocatorTest(const InlineLocatorTest& other);
            InlineLocatorTest& operator = (const InlineLocatorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_INLINELOCATORTEST_H_ */
