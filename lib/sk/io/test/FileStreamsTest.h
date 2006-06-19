/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILESTREAMSTEST_
#define _SK_IO_TEST_FILESTREAMSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileStreamsTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileStreamsTest);
          CPPUNIT_TEST(testRead);
          CPPUNIT_TEST(testWriteOpen);
          CPPUNIT_TEST(testDescriptorsSame);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileStreamsTest();
          virtual ~FileStreamsTest();
          
          void setUp();
          void tearDown();
          void testRead();
          void testWriteOpen();
          void testDescriptorsSame();
          
        private:
          FileStreamsTest(const FileStreamsTest& other);
          FileStreamsTest& operator = (const FileStreamsTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILESTREAMSTEST_ */
