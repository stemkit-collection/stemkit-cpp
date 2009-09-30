/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_BYTEARRAYOUTPUTSTREAMTEST_
#define _SK_IO_TEST_BYTEARRAYOUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class ByteArrayOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::ByteArrayOutputStreamTest);
          CPPUNIT_TEST(testWriteToContainer);
          CPPUNIT_TEST(testWriteToCharBuffer);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ByteArrayOutputStreamTest();
          virtual ~ByteArrayOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testWriteToContainer();
          void testWriteToCharBuffer();
          
        private:
          ByteArrayOutputStreamTest(const ByteArrayOutputStreamTest& other);
          ByteArrayOutputStreamTest& operator = (const ByteArrayOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_BYTEARRAYOUTPUTSTREAMTEST_ */
