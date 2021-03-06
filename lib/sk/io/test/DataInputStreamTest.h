/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_DATAINPUTSTREAMTEST_
#define _SK_IO_TEST_DATAINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include <vector>

namespace sk {
  namespace io {
    class InputStream;
    class DataInput;

    namespace test {
      class DataInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::DataInputStreamTest);
          CPPUNIT_TEST(testReadFromEmpty);
          CPPUNIT_TEST(testReadChar);
          CPPUNIT_TEST(testReadLine);
          CPPUNIT_TEST(testReadInt);
        CPPUNIT_TEST_SUITE_END();

        public:
          DataInputStreamTest();
          virtual ~DataInputStreamTest();

          void setUp();
          void tearDown();
          void testReadFromEmpty();
          void testReadChar();
          void testReadLine();
          void testReadInt();

        private:
          DataInputStreamTest(const DataInputStreamTest& other);
          DataInputStreamTest& operator = (const DataInputStreamTest& other);

          std::vector<char>& buffer() {
            return _bufferHolder.getMutable();
          }
          sk::io::DataInput& stream() {
            return _dataStreamHolder.getMutable();
          }
          sk::util::Holder<std::vector<char> > _bufferHolder;
          sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
          sk::util::Holder<sk::io::DataInput> _dataStreamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_DATAINPUTSTREAMTEST_ */
