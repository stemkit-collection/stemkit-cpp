/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_TEST_COUNTINGINPUTSTREAMTEST_H_
#define _SK_IO_TEST_COUNTINGINPUTSTREAMTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class CountingInputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::CountingInputStreamTest);
          CPPUNIT_TEST(testCounting);
        CPPUNIT_TEST_SUITE_END();

        public:
          CountingInputStreamTest();
          virtual ~CountingInputStreamTest();

          void setUp();
          void tearDown();
          void testCounting();

        private:
          CountingInputStreamTest(const CountingInputStreamTest& other);
          CountingInputStreamTest& operator = (const CountingInputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_COUNTINGINPUTSTREAMTEST_H_ */
