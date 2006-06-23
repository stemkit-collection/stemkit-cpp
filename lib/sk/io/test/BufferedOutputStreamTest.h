/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_BUFFEREDOUTPUTSTREAMTEST_
#define _SK_IO_TEST_BUFFEREDOUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class BufferedOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::BufferedOutputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          BufferedOutputStreamTest();
          virtual ~BufferedOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          BufferedOutputStreamTest(const BufferedOutputStreamTest& other);
          BufferedOutputStreamTest& operator = (const BufferedOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_BUFFEREDOUTPUTSTREAMTEST_ */
