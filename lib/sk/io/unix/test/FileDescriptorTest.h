/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEDESCRIPTORTEST_
#define _SK_IO_TEST_FILEDESCRIPTORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include <sk/io/FileDescriptor.h>

namespace sk {
  namespace io {
    namespace test {
      class FileDescriptorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileDescriptorTest);
          CPPUNIT_TEST(testClone);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileDescriptorTest();
          virtual ~FileDescriptorTest();
          
          void setUp();
          void tearDown();
          void testClone();
          
        private:
          FileDescriptorTest(const FileDescriptorTest& other);
          FileDescriptorTest& operator = (const FileDescriptorTest& other);

          sk::io::FileDescriptor& input() {
            return _readDescriptor.getMutable();
          }
          sk::io::FileDescriptor& output() {
            return _writeDescriptor.getMutable();
          }
          sk::util::Holder<FileDescriptor> _readDescriptor;
          sk::util::Holder<FileDescriptor> _writeDescriptor;
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEDESCRIPTORTEST_ */
