/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_TESTS_SCOPETEST_
#define _SK_RT_TESTS_SCOPETEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>

namespace sk {
  namespace rt {
    namespace tests {
      class ScopeTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::rt::tests::ScopeTest);
          CPPUNIT_TEST(testDefaultNoOutputButError);
          CPPUNIT_TEST(testDefaultNoOutputUnlessMessages);
          CPPUNIT_TEST(testConcatenation);
          CPPUNIT_TEST(testScope);
          CPPUNIT_TEST(testDefaultProperties);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ScopeTest();
          virtual ~ScopeTest();
          
          void setUp();
          void tearDown();
          void testDefaultNoOutputButError();
          void testDefaultNoOutputUnlessMessages();
          void testConcatenation();
          void testScope();
          void testDefaultProperties();
          
        private:
          ScopeTest(const ScopeTest& other);
          ScopeTest& operator = (const ScopeTest& other);
          std::ostringstream _stream;
      };
    }
  }
}

#endif /* _SK_RT_TESTS_SCOPETEST_ */
