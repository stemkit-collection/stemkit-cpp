/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_PTYTEST_
#define _SK_IO_TEST_PTYTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class PtyTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::PtyTest);
          CPPUNIT_TEST(testAsPipe);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          PtyTest();
          virtual ~PtyTest();
          
          void setUp();
          void tearDown();
          void testAsPipe();
          
        private:
          PtyTest(const PtyTest& other);
          PtyTest& operator = (const PtyTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_PTYTEST_ */
