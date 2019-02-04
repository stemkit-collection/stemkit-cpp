/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_FILETEST_
#define _SK_IO_TEST_FILETEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class FileTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::FileTest);
          CPPUNIT_TEST(testOpenRead);
          CPPUNIT_TEST(testOpenUnexistent);
          CPPUNIT_TEST(testOpenWrite);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          FileTest();
          virtual ~FileTest();
          
          void setUp();
          void tearDown();
          void testOpenRead();
          void testOpenUnexistent();
          void testOpenWrite();
          
        private:
          FileTest(const FileTest& other);
          FileTest& operator = (const FileTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_FILETEST_ */
