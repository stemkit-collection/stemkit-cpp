/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_BUFFEREDINPUTSTREAMTEST_
#define _SK_IO_TEST_BUFFEREDINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class BufferedInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::BufferedInputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          BufferedInputStreamTest();
          virtual ~BufferedInputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          BufferedInputStreamTest(const BufferedInputStreamTest& other);
          BufferedInputStreamTest& operator = (const BufferedInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_BUFFEREDINPUTSTREAMTEST_ */
