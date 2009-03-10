/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SCOPE_TEST_CONFIGBLOCKLOOKUPTEST_H_
#define _SK_RT_SCOPE_TEST_CONFIGBLOCKLOOKUPTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace scope {
      class XmlProcessor;
      class Aggregator;

      namespace test {
        class ConfigBlockLookupTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::scope::test::ConfigBlockLookupTest);
            CPPUNIT_TEST(testExactMatch);
            CPPUNIT_TEST(testNonExistentAndNoDefault);
            CPPUNIT_TEST(testNonExistentGetsDefault);
            CPPUNIT_TEST(testRequestingEmptyGetsFirst);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            ConfigBlockLookupTest();
            virtual ~ConfigBlockLookupTest();
        
            void setUp();
            void tearDown();
            void testExactMatch();
            void testNonExistentAndNoDefault();
            void testNonExistentGetsDefault();
            void testRequestingEmptyGetsFirst();
        
          private:
            ConfigBlockLookupTest(const ConfigBlockLookupTest& other);
            ConfigBlockLookupTest& operator = (const ConfigBlockLookupTest& other);

            XmlProcessor& processor();

            sk::util::Holder<Aggregator> _aggregatorHolder;
            sk::util::Holder<XmlProcessor> _processorHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_SCOPE_TEST_CONFIGBLOCKLOOKUPTEST_H_ */
