/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_COLLECTION_INJECTORTEST_H_
#define _SK_UTIL_TEST_COLLECTION_INJECTORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace util {
    namespace test {
      namespace collection {
        class InjectorTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::util::test::collection::InjectorTest);
            CPPUNIT_TEST(testBasics);
            CPPUNIT_TEST(testJoinStrings);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            InjectorTest();
            virtual ~InjectorTest();
        
            void setUp();
            void tearDown();
            void testBasics();
            void testJoinStrings();
        
          private:
            InjectorTest(const InjectorTest& other);
            InjectorTest& operator = (const InjectorTest& other);
        };
      }
    }
  }
}

#endif /* _SK_UTIL_TEST_COLLECTION_INJECTORTEST_H_ */
