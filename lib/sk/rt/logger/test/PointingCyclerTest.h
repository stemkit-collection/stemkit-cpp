/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_LOGGER_TEST_POINTINGCYCLERTEST_
#define _SK_RT_LOGGER_TEST_POINTINGCYCLERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace logger {
      class FileDestination;
      class PipeDestination;

      namespace test {
        class PointingCyclerTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::logger::test::PointingCyclerTest);
            CPPUNIT_TEST(testDefaults);
            CPPUNIT_TEST(testEarlyMakeReady);
            CPPUNIT_TEST(testDelayedDispatch);
            CPPUNIT_TEST(testMessageOnExit);
            CPPUNIT_TEST(testMessageOnExit);
            CPPUNIT_TEST(testWriteErrorAfterClose);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            PointingCyclerTest();
            virtual ~PointingCyclerTest();
            
            void setUp();
            void tearDown();
            void testDefaults();
            void testEarlyMakeReady();
            void testDelayedDispatch();
            void testMessageOnExit();
            void testWriteErrorAfterClose();
            
          private:
            PointingCyclerTest(const PointingCyclerTest& other);
            PointingCyclerTest& operator = (const PointingCyclerTest& other);

            sk::util::Holder<logger::FileDestination> _fileHolder;
            sk::util::Holder<logger::PipeDestination> _pipeHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_TEST_POINTINGCYCLERTEST_ */
