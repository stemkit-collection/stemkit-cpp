/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_WIN32_TEST_SYSTEMEXCEPTIONTEST_H_
#define _SK_RT_WIN32_TEST_SYSTEMEXCEPTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace rt {
    namespace win32 {
      namespace test {
        class SystemExceptionTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::win32::test::SystemExceptionTest);
            CPPUNIT_TEST(testBadHandle);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            SystemExceptionTest();
            virtual ~SystemExceptionTest();
        
            void setUp();
            void tearDown();
            void testBadHandle();
        
          private:
            SystemExceptionTest(const SystemExceptionTest& other);
            SystemExceptionTest& operator = (const SystemExceptionTest& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_WIN32_TEST_SYSTEMEXCEPTIONTEST_H_ */
