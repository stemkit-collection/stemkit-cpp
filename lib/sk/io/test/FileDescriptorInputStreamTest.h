/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEDESCRIPTORINPUTSTREAMTEST_
#define _SK_IO_TEST_FILEDESCRIPTORINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileDescriptorInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileDescriptorInputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileDescriptorInputStreamTest();
          virtual ~FileDescriptorInputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          FileDescriptorInputStreamTest(const FileDescriptorInputStreamTest& other);
          FileDescriptorInputStreamTest& operator = (const FileDescriptorInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEDESCRIPTORINPUTSTREAMTEST_ */
