/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_TEST_ALIASINGPROCESSORTEST_H_
#define _SK_UTIL_TEST_ALIASINGPROCESSORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class AliasingProcessorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::AliasingProcessorTest);
          CPPUNIT_TEST(testAliasing);
        CPPUNIT_TEST_SUITE_END();

        public:
          AliasingProcessorTest();
          virtual ~AliasingProcessorTest();

          void setUp();
          void tearDown();
          void testAliasing();

        private:
          AliasingProcessorTest(const AliasingProcessorTest& other);
          AliasingProcessorTest& operator = (const AliasingProcessorTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_ALIASINGPROCESSORTEST_H_ */
