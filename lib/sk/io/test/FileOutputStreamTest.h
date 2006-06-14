/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEOUTPUTSTREAMTEST_
#define _SK_IO_TEST_FILEOUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileOutputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileOutputStreamTest();
          virtual ~FileOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          FileOutputStreamTest(const FileOutputStreamTest& other);
          FileOutputStreamTest& operator = (const FileOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEOUTPUTSTREAMTEST_ */
