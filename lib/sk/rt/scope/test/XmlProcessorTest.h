/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_SCOPE_TEST_XMLPROCESSORTEST_
#define _SK_RT_SCOPE_TEST_XMLPROCESSORTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace rt {
    namespace scope {
      class Aggregator;

      namespace test {
        class XmlProcessorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::rt::scope::test::XmlProcessorTest);
            CPPUNIT_TEST(testEmpty);
            CPPUNIT_TEST(testTopOnly);
            CPPUNIT_TEST(testTopLogInfo);
            CPPUNIT_TEST(testValueSubstituion);
          CPPUNIT_TEST_SUITE_END();

          public:
            XmlProcessorTest();
            virtual ~XmlProcessorTest();

            void setUp();
            void tearDown();
            void testEmpty();
            void testTopOnly();
            void testTopLogInfo();
            void testValueSubstituion();

          private:
            XmlProcessorTest(const XmlProcessorTest& other);
            XmlProcessorTest& operator = (const XmlProcessorTest& other);

            sk::util::Holder<sk::rt::scope::Aggregator> _aggregatorHolder;
        };
      }
    }
  }
}

#endif /* _SK_RT_SCOPE_TEST_XMLPROCESSORTEST_ */
