/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_TESTS_AGGREGATORTEST_
#define _SK_RT_TESTS_AGGREGATORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace tests {
      class AggregatorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::AggregatorTest);
          CPPUNIT_TEST(testInner);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AggregatorTest();
          virtual ~AggregatorTest();
          
          void setUp();
          void tearDown();
          void testInner();
          
        private:
          AggregatorTest(const AggregatorTest& other);
          AggregatorTest& operator = (const AggregatorTest& other);
      };
    }
  }
}

#endif /* _SK_RT_TESTS_AGGREGATORTEST_ */
