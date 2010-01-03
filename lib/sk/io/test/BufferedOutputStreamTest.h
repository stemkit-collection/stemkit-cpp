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
#include <sk/util/Container.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace io {
    class OutputStream;

    namespace test {
      class MockOutputStream;

      class BufferedOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::BufferedOutputStreamTest);
          CPPUNIT_TEST(testBuffer);
          CPPUNIT_TEST(testFlushOnClose);
          CPPUNIT_TEST(testWriteLargerChunk);
          CPPUNIT_TEST(testNoBuffer);
          CPPUNIT_TEST(testBufferLimitedWrite);
          CPPUNIT_TEST(testZeroWrite);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          BufferedOutputStreamTest();
          virtual ~BufferedOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testBuffer();
          void testFlushOnClose();
          void testWriteLargerChunk();
          void testNoBuffer();
          void testBufferLimitedWrite();
          void testZeroWrite();
          
        private:
          BufferedOutputStreamTest(const BufferedOutputStreamTest& other);
          BufferedOutputStreamTest& operator = (const BufferedOutputStreamTest& other);

          MockOutputStream& mock() {
            return _mockHolder.getMutable();
          }
          sk::io::OutputStream& stream() {
            return _streamHolder.getMutable();
          }
          sk::util::Holder<MockOutputStream> _mockHolder;
          sk::util::Holder<sk::io::OutputStream> _streamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_BUFFEREDOUTPUTSTREAMTEST_ */
