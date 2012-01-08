/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_TEST_PIPEPROCESSLEFTOVERTEST_
#define _SK_RT_LOGGER_TEST_PIPEPROCESSLEFTOVERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace logger {
      namespace test {
        class PipeProcessLeftoverTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::logger::test::PipeProcessLeftoverTest);
            CPPUNIT_TEST(testNoLeftovers);
          CPPUNIT_TEST_SUITE_END();

          public:
            PipeProcessLeftoverTest();
            virtual ~PipeProcessLeftoverTest();

            void setUp();
            void tearDown();
            void testNoLeftovers();

          private:
            PipeProcessLeftoverTest(const PipeProcessLeftoverTest& other);
            PipeProcessLeftoverTest& operator = (const PipeProcessLeftoverTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_TEST_PIPEPROCESSLEFTOVERTEST_ */
