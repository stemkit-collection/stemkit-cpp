/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_TEST_ANONYMOUSPIPETEST_
#define _SK_IO_TEST_ANONYMOUSPIPETEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace io {
    namespace test {
      class AnonymousPipeTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::io::test::AnonymousPipeTest);
          CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          AnonymousPipeTest();
          virtual ~AnonymousPipeTest();
          
          void setUp();
          void tearDown();
          void testCreate();
          
        private:
          AnonymousPipeTest(const AnonymousPipeTest& other);
          AnonymousPipeTest& operator = (const AnonymousPipeTest& other);
      };
    }
  }
}

#endif /* _SK_IO_TEST_ANONYMOUSPIPETEST_ */
