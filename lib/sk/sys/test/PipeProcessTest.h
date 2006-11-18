/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_PIPEPROCESSTEST_
#define _SK_SYS_TEST_PIPEPROCESSTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class PipeProcessTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::PipeProcessTest);
          CPPUNIT_TEST(testTranslate);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          PipeProcessTest();
          virtual ~PipeProcessTest();
          
          void setUp();
          void tearDown();
          void testTranslate();
          
        private:
          PipeProcessTest(const PipeProcessTest& other);
          PipeProcessTest& operator = (const PipeProcessTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_PIPEPROCESSTEST_ */
