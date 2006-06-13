/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_TRASHDISPOSERTEST_
#define _SK_SYS_TEST_TRASHDISPOSERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class TrashDisposerTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::TrashDisposerTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          TrashDisposerTest();
          virtual ~TrashDisposerTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          TrashDisposerTest(const TrashDisposerTest& other);
          TrashDisposerTest& operator = (const TrashDisposerTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_TRASHDISPOSERTEST_ */
