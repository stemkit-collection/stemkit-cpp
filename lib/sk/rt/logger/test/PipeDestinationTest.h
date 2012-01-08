/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_TEST_PIPEDESTINATIONTEST_
#define _SK_RT_LOGGER_TEST_PIPEDESTINATIONTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include "scope/NullArbitrator.h"

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination;
      class PipeDestination;

      namespace test {
        class PipeDestinationTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::logger::test::PipeDestinationTest);
            CPPUNIT_TEST(testDefaults);
            CPPUNIT_TEST(testEarlyMakeReady);
            CPPUNIT_TEST(testDelayedDispatch);
            CPPUNIT_TEST(testMessageOnExit);
            CPPUNIT_TEST(testMessageOnExit);
            CPPUNIT_TEST(testWriteErrorAfterClose);
          CPPUNIT_TEST_SUITE_END();

          public:
            PipeDestinationTest();
            virtual ~PipeDestinationTest();

            void setUp();
            void tearDown();
            void testDefaults();
            void testEarlyMakeReady();
            void testDelayedDispatch();
            void testMessageOnExit();
            void testWriteErrorAfterClose();

          private:
            PipeDestinationTest(const PipeDestinationTest& other);
            PipeDestinationTest& operator = (const PipeDestinationTest& other);

            sk::util::Holder<logger::FileDestination> _fileHolder;
            sk::util::Holder<logger::PipeDestination> _pipeHolder;
            scope::NullArbitrator _arbitrator;
        };
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_TEST_PIPEDESTINATIONTEST_ */
