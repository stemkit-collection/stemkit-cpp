/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_DATAINPUTSTREAMTEST_
#define _SK_IO_TEST_DATAINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class DataInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::DataInputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          DataInputStreamTest();
          virtual ~DataInputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          DataInputStreamTest(const DataInputStreamTest& other);
          DataInputStreamTest& operator = (const DataInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_DATAINPUTSTREAMTEST_ */
