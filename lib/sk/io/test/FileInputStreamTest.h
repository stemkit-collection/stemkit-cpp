/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILEINPUTSTREAMTEST_
#define _SK_IO_TEST_FILEINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileInputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileInputStreamTest();
          virtual ~FileInputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          FileInputStreamTest(const FileInputStreamTest& other);
          FileInputStreamTest& operator = (const FileInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILEINPUTSTREAMTEST_ */
