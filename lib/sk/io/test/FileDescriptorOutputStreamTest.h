/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEDESCRIPTOROUTPUTSTREAMTEST_
#define _SK_IO_TEST_FILEDESCRIPTOROUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileDescriptorOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileDescriptorOutputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileDescriptorOutputStreamTest();
          virtual ~FileDescriptorOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          FileDescriptorOutputStreamTest(const FileDescriptorOutputStreamTest& other);
          FileDescriptorOutputStreamTest& operator = (const FileDescriptorOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEDESCRIPTOROUTPUTSTREAMTEST_ */
