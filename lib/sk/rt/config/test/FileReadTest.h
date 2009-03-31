/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_FILEREADTEST_
#define _SK_RT_CONFIG_TEST_FILEREADTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class FileReadTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::config::test::FileReadTest);
            CPPUNIT_TEST(testReadFileFromCwd);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            FileReadTest();
            virtual ~FileReadTest();
            
            void setUp();
            void tearDown();
            void testReadFileFromCwd();
            
          private:
            FileReadTest(const FileReadTest& other);
            FileReadTest& operator = (const FileReadTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_FILEREADTEST_ */
