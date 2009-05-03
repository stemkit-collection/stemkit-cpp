/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_PROPERTIESTEST_H_
#define _SK_UTIL_TEST_PROPERTIESTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class PropertiesTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::PropertiesTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testGetWithDefaults);
          CPPUNIT_TEST(testSetKinds);
          CPPUNIT_TEST(testDump);
          CPPUNIT_TEST(testDelete);
          CPPUNIT_TEST(testForEach);
          CPPUNIT_TEST(testParse);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          PropertiesTest();
          virtual ~PropertiesTest();
      
          void setUp();
          void tearDown();
          void testBasics();
          void testGetWithDefaults();
          void testSetKinds();
          void testDump();
          void testDelete();
          void testForEach();
          void testParse();
      
        private:
          PropertiesTest(const PropertiesTest& other);
          PropertiesTest& operator = (const PropertiesTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_PROPERTIESTEST_H_ */
