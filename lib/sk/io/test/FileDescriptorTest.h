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

namespace sk {
  namespace io {
    namespace test {
      class FileDescriptorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileDescriptorTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileDescriptorTest();
          virtual ~FileDescriptorTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          FileDescriptorTest(const FileDescriptorTest& other);
          FileDescriptorTest& operator = (const FileDescriptorTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEDESCRIPTORTEST_ */
