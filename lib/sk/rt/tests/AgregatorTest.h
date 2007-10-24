/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_TESTS_AGREGATORTEST_
#define _SK_RT_TESTS_AGREGATORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class AgregatorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::AgregatorTest);
          CPPUNIT_TEST(testInner);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AgregatorTest();
          virtual ~AgregatorTest();
          
          void setUp();
          void tearDown();
          void testInner();
          
        private:
          AgregatorTest(const AgregatorTest& other);
          AgregatorTest& operator = (const AgregatorTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_AGREGATORTEST_ */
