/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_TEST_COUNTINGOUTPUTSTREAMTEST_H_
#define _SK_IO_TEST_COUNTINGOUTPUTSTREAMTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class CountingOutputStreamTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::CountingOutputStreamTest);
          CPPUNIT_TEST(testCounting);
        CPPUNIT_TEST_SUITE_END();

        public:
          CountingOutputStreamTest();
          virtual ~CountingOutputStreamTest();

          void setUp();
          void tearDown();
          void testCounting();

        private:
          CountingOutputStreamTest(const CountingOutputStreamTest& other);
          CountingOutputStreamTest& operator = (const CountingOutputStreamTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_COUNTINGOUTPUTSTREAMTEST_H_ */
