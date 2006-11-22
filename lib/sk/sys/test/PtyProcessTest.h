/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_PTYPROCESSTEST_
#define _SK_SYS_TEST_PTYPROCESSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class PtyProcessTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::PtyProcessTest);
          CPPUNIT_TEST(testTranslate);
          CPPUNIT_TEST(testTty);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          PtyProcessTest();
          virtual ~PtyProcessTest();
          
          void setUp();
          void tearDown();
          void testTranslate();
          void testTty();
          
        private:
          PtyProcessTest(const PtyProcessTest& other);
          PtyProcessTest& operator = (const PtyProcessTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_PTYPROCESSTEST_ */
