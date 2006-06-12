/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_POINTERSLOTTEST_
#define _SK_UTIL_TEST_POINTERSLOTTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      class PointerSlotTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::PointerSlotTest);
          CPPUNIT_TEST(testGet);
          CPPUNIT_TEST(testDeprive);
          CPPUNIT_TEST(testMisc);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          PointerSlotTest();
          virtual ~PointerSlotTest();
          
          void setUp();
          void tearDown();
          void testGet();
          void testDeprive();
          void testMisc();
          
        private:
          PointerSlotTest(const PointerSlotTest& other);
          PointerSlotTest& operator = (const PointerSlotTest& other);
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PointerSlotTest);

#endif /* _SK_UTIL_TEST_POINTERSLOTTEST_ */
