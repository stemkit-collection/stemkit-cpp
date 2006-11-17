/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_TRACERTEST_
#define _SK_SYS_TEST_TRACERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class TracerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::TracerTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          TracerTest();
          virtual ~TracerTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          TracerTest(const TracerTest& other);
          TracerTest& operator = (const TracerTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_TRACERTEST_ */
