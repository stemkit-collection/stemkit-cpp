/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_TEST_OBJECTTEST_
#define _SK_UTIL_TEST_OBJECTTEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

namespace sk {
  namespace util {
    class Object;

    namespace test {
      class ObjectTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::util::test::ObjectTest);
          CPPUNIT_TEST(testClassName);
          CPPUNIT_TEST(testId);
          CPPUNIT_TEST(testToString);
        CPPUNIT_TEST_SUITE_END();
        
        public:
          ObjectTest();
          virtual ~ObjectTest();
          
          void setUp();
          void tearDown();
          void testClassName();
          void testId();
          void testToString();
          
        private:
          ObjectTest(const ObjectTest& other);
          ObjectTest& operator = (const ObjectTest& other);

          const sk::util::Object& getObject() const;
          std::auto_ptr<util::Object> _object;
      };
    }
  }
}

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ObjectTest);

#endif /* _SK_UTIL_TEST_OBJECTTEST_ */
