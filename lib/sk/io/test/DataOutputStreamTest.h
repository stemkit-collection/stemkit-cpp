/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_DATAOUTPUTSTREAMTEST_
#define _SK_IO_TEST_DATAOUTPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class DataOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::DataOutputStreamTest);
          CPPUNIT_TEST(testSimple);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          DataOutputStreamTest();
          virtual ~DataOutputStreamTest();
          
          void setUp();
          void tearDown();
          void testSimple();
          
        private:
          DataOutputStreamTest(const DataOutputStreamTest& other);
          DataOutputStreamTest& operator = (const DataOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_DATAOUTPUTSTREAMTEST_ */
