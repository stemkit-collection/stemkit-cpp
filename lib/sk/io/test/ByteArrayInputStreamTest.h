/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_BYTEARRAYINPUTSTREAMTEST_
#define _SK_IO_TEST_BYTEARRAYINPUTSTREAMTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class ByteArrayInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::ByteArrayInputStreamTest);
          CPPUNIT_TEST(testEmpty);
          CPPUNIT_TEST(testReadOneByOne);
          CPPUNIT_TEST(testReadByVector);
          CPPUNIT_TEST(testSkip);
          CPPUNIT_TEST(testMarkReset);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ByteArrayInputStreamTest();
          virtual ~ByteArrayInputStreamTest();
          
          void setUp();
          void tearDown();
          void testEmpty();
          void testReadOneByOne();
          void testReadByVector();
          void testSkip();
          void testMarkReset();
          
        private:
          ByteArrayInputStreamTest(const ByteArrayInputStreamTest& other);
          ByteArrayInputStreamTest& operator = (const ByteArrayInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_BYTEARRAYINPUTSTREAMTEST_ */
