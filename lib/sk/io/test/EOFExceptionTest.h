/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_EOFEXCEPTIONTEST_
#define _SK_IO_TEST_EOFEXCEPTIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class EOFExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::EOFExceptionTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          EOFExceptionTest();
          virtual ~EOFExceptionTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          EOFExceptionTest(const EOFExceptionTest& other);
          EOFExceptionTest& operator = (const EOFExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_EOFEXCEPTIONTEST_ */
