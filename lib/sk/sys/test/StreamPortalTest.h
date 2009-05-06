/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_SYS_TEST_STREAMPORTALTEST_H_
#define _SK_SYS_TEST_STREAMPORTALTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sk/rt/Environment.h>

namespace sk {
  namespace sys {
    namespace test {
      class StreamPortalTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::sys::test::StreamPortalTest);
          CPPUNIT_TEST(testStreams);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          StreamPortalTest();
          virtual ~StreamPortalTest();
      
          void setUp();
          void tearDown();
          void testStreams();
      
        private:
          StreamPortalTest(const StreamPortalTest& other);
          StreamPortalTest& operator = (const StreamPortalTest& other);

          sk::rt::Environment _environment;
      };
    }
  }
}

#endif /* _SK_SYS_TEST_STREAMPORTALTEST_H_ */
