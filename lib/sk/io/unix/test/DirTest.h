/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_TEST_DIRTEST_H_
#define _SK_IO_TEST_DIRTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class DirTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::DirTest);
          CPPUNIT_TEST(testEachEntry);
          CPPUNIT_TEST(testEachRegularFile);
        CPPUNIT_TEST_SUITE_END();

        public:
          DirTest();
          virtual ~DirTest();

          void setUp();
          void tearDown();
          void testEachEntry();
          void testEachRegularFile();

        private:
          DirTest(const DirTest& other);
          DirTest& operator = (const DirTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_DIRTEST_H_ */
