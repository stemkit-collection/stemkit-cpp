/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_CONTAINERTEST_
#define _SK_UTIL_TEST_CONTAINERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class ContainerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ContainerTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ContainerTest();
          virtual ~ContainerTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          ContainerTest(const ContainerTest& other);
          ContainerTest& operator = (const ContainerTest& other);
      };
    }
  }
}

#endif /* _SK_UTIL_TEST_CONTAINERTEST_ */
