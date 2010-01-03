/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_DATAOUTPUTSTREAMTEST_
#define _SK_IO_TEST_DATAOUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include <vector>

namespace sk {
  namespace io {
    class OutputStream;
    class DataOutput;

    namespace test {
      class DataOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::DataOutputStreamTest);
          CPPUNIT_TEST(testWriteChar);
          CPPUNIT_TEST(testWriteChars);
          CPPUNIT_TEST(testWriteInt);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          DataOutputStreamTest();
          virtual ~DataOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testWriteChar();
          void testWriteChars();
          void testWriteInt();
          
        private:
          DataOutputStreamTest(const DataOutputStreamTest& other);
          DataOutputStreamTest& operator = (const DataOutputStreamTest& other);

          std::vector<char>& buffer() {
            return _bufferHolder.getMutable();
          }
          sk::io::DataOutput& stream() {
            return _dataStreamHolder.getMutable();
          }
          sk::util::Holder<std::vector<char> > _bufferHolder;
          sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
          sk::util::Holder<sk::io::DataOutput> _dataStreamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_DATAOUTPUTSTREAMTEST_ */
