/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_TEST_STABLEHEADCYCLERTEST_
#define _SK_RT_LOGGER_TEST_STABLEHEADCYCLERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>
#include "scope/NullArbitrator.h"

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination;

      namespace test {
        class StableHeadCyclerTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::logger::test::StableHeadCyclerTest);
            CPPUNIT_TEST(testDefaults);
            CPPUNIT_TEST(testEarlyMakeReady);
            CPPUNIT_TEST(testDelayedDispatch);
          CPPUNIT_TEST_SUITE_END();

          public:
            StableHeadCyclerTest();
            virtual ~StableHeadCyclerTest();

            void setUp();
            void tearDown();
            void testDefaults();
            void testEarlyMakeReady();
            void testDelayedDispatch();

          private:
            StableHeadCyclerTest(const StableHeadCyclerTest& other);
            StableHeadCyclerTest& operator = (const StableHeadCyclerTest& other);

            sk::util::Holder<logger::FileDestination> _fileHolder;
            scope::NullArbitrator _arbitrator;
        };
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_TEST_STABLEHEADCYCLERTEST_ */
