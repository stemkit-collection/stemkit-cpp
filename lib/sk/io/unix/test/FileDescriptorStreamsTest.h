/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEDESCRIPTORSTREAMSTEST_
#define _SK_IO_TEST_FILEDESCRIPTORSTREAMSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace io {
    class InputStream;
    class OutputStream;
    class DataInput;
    class DataOutput;

    namespace test {
      class FileDescriptorStreamsTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileDescriptorStreamsTest);
          CPPUNIT_TEST(testReadWrite);
          CPPUNIT_TEST(testClose);
          CPPUNIT_TEST(testCloseOnDestruction);
          CPPUNIT_TEST(testPartialReadOnEof);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileDescriptorStreamsTest();
          virtual ~FileDescriptorStreamsTest();
          
          void setUp();
          void tearDown();
          void testReadWrite();
          void testClose();
          void testCloseOnDestruction();
          void testPartialReadOnEof();
          
        private:
          FileDescriptorStreamsTest(const FileDescriptorStreamsTest& other);
          FileDescriptorStreamsTest& operator = (const FileDescriptorStreamsTest& other);

          sk::io::InputStream& input() {
            return _inputStreamHolder.getMutable();
          }
          sk::io::OutputStream& output() {
            return _outputStreamHolder.getMutable();
          }
          sk::io::DataInput& dataInput() {
            return _dataInputStreamHolder.getMutable();
          }
          sk::io::DataOutput& dataOutput() {
            return _dataOutputStreamHolder.getMutable();
          }

          sk::util::Holder<sk::io::InputStream> _inputStreamHolder;
          sk::util::Holder<sk::io::OutputStream> _outputStreamHolder;
          sk::util::Holder<sk::io::DataInput> _dataInputStreamHolder;
          sk::util::Holder<sk::io::DataOutput> _dataOutputStreamHolder;
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEDESCRIPTORSTREAMSTEST_ */
