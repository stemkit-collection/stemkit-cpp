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
      class BufferedOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::BufferedOutputStreamTest);
          CPPUNIT_TEST(testBuffer);
          CPPUNIT_TEST(testFlushOnClose);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          BufferedOutputStreamTest();
          virtual ~BufferedOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testBuffer();
          void testFlushOnClose();
          
        private:
          BufferedOutputStreamTest(const BufferedOutputStreamTest& other);
          BufferedOutputStreamTest& operator = (const BufferedOutputStreamTest& other);

          sk::util::Container& container() {
            return _containerHolder.get();
          }
          sk::io::OutputStream& stream() {
            return _streamHolder.get();
          }
          sk::io::OutputStream& output() {
            return _outputHolder.get();
          }
          sk::util::Holder<sk::util::Container> _containerHolder;
          sk::util::Holder<sk::io::OutputStream> _outputHolder;
          sk::util::Holder<sk::io::OutputStream> _streamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_BUFFEREDOUTPUTSTREAMTEST_ */
