/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_INSPECTTEST_H_
#define _SK_UTIL_TEST_INSPECTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class InspectTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::InspectTest);
          CPPUNIT_TEST(testCharBuffers);
          CPPUNIT_TEST(testStrings);
          CPPUNIT_TEST(testVectors);
          CPPUNIT_TEST(testLists);
          CPPUNIT_TEST(testDeques);
          CPPUNIT_TEST(testContent);
        CPPUNIT_TEST_SUITE_END();

        public:
          InspectTest();
          virtual ~InspectTest();

          void setUp();
          void tearDown();
          void testCharBuffers();
          void testStrings();
          void testVectors();
          void testLists();
          void testDeques();
          void testContent();

        private:
          InspectTest(const InspectTest& other);
          InspectTest& operator = (const InspectTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_INSPECTTEST_H_ */
