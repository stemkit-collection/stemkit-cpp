/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_TEST_XMLCONFIGLOADERTEST_
#define _SK_RT_SCOPE_TEST_XMLCONFIGLOADERTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;

      namespace test {
        class XmlConfigLoaderTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::scope::test::XmlConfigLoaderTest);
            CPPUNIT_TEST(testBigPicture);
            CPPUNIT_TEST(testSubScopes);
          CPPUNIT_TEST_SUITE_END();
          
          public:
            XmlConfigLoaderTest();
            virtual ~XmlConfigLoaderTest();
            
            void setUp();
            void tearDown();
            void testBigPicture();
            void testSubScopes();
            
          private:
            XmlConfigLoaderTest(const XmlConfigLoaderTest& other);
            XmlConfigLoaderTest& operator = (const XmlConfigLoaderTest& other);

            Aggregator& aggregator();

            sk::util::Holder<Aggregator> _aggregatorHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_SCOPE_TEST_XMLCONFIGLOADERTEST_ */
