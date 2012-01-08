/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PP_TEST_PRIMENODETEST_H_
#define _SK_UTIL_PP_TEST_PRIMENODETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace pp {
      namespace test {
        class PrimeNodeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::pp::test::PrimeNodeTest);
            CPPUNIT_TEST(testOpenBrakets);
            CPPUNIT_TEST(testPointer);
          CPPUNIT_TEST_SUITE_END();

          public:
            PrimeNodeTest();
            virtual ~PrimeNodeTest();

            void setUp();
            void tearDown();
            void testOpenBrakets();
            void testPointer();

          private:
            PrimeNodeTest(const PrimeNodeTest& other);
            PrimeNodeTest& operator = (const PrimeNodeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_PP_TEST_PRIMENODETEST_H_ */
