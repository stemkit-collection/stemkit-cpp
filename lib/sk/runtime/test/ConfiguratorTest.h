/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RUNTIME_TEST_CONFIGURATORTEST_
#define _SK_RUNTIME_TEST_CONFIGURATORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace runtime {
    namespace test {
      class ConfiguratorTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::runtime::test::ConfiguratorTest);
          CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ConfiguratorTest();
          virtual ~ConfiguratorTest();
          
          void setUp();
          void tearDown();
          void testCreate();
          
        private:
          ConfiguratorTest(const ConfiguratorTest& other);
          ConfiguratorTest& operator = (const ConfiguratorTest& other);
      };
    }
  }
}

#endif /* _SK_RUNTIME_TEST_CONFIGURATORTEST_ */
