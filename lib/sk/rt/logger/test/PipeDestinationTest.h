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

namespace sk {
  namespace rt {
    namespace logger {
      namespace test {
        class PipeDestinationTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::logger::test::PipeDestinationTest);
            CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            PipeDestinationTest();
            virtual ~PipeDestinationTest();
            
            void setUp();
            void tearDown();
            void testBasics();
            
          private:
            PipeDestinationTest(const PipeDestinationTest& other);
            PipeDestinationTest& operator = (const PipeDestinationTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_LOGGER_TEST_PIPEDESTINATIONTEST_ */
