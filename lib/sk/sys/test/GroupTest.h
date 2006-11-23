/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_SYS_TEST_GROUPTEST_
#define _SK_SYS_TEST_GROUPTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace sys {
    namespace test {
      class GroupTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::GroupTest);
          CPPUNIT_TEST(testFind);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          GroupTest();
          virtual ~GroupTest();
          
          void setUp();
          void tearDown();
          void testFind();
          
        private:
          GroupTest(const GroupTest& other);
          GroupTest& operator = (const GroupTest& other);
      };
    }
  }
}

#endif /* _SK_SYS_TEST_GROUPTEST_ */
