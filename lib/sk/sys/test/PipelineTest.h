/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_PIPELINETEST_
#define _SK_SYS_TEST_PIPELINETEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class PipelineTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::PipelineTest);
          CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST_SUITE_END();

        public:
          PipelineTest();
          virtual ~PipelineTest();

          void setUp();
          void tearDown();
          void testCreate();

        private:
          PipelineTest(const PipelineTest& other);
          PipelineTest& operator = (const PipelineTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_PIPELINETEST_ */
