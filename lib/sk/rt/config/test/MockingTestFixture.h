/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_RT_CONFIG_TEST_MOCKINGTESTFIXTURE_
#define _SK_RT_CONFIG_TEST_MOCKINGTESTFIXTURE_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sk/rt/config/NamedStreamOpener.h>

namespace sk {
  namespace rt {
    namespace config {
      namespace test {
        class MockingTestFixture
          : public CppUnit::TestFixture,
            public virtual sk::rt::config::NamedStreamOpener
        {
          public:
            MockingTestFixture();
            virtual ~MockingTestFixture();

            void setUp();
            void tearDown();

            // sk::rt::config::NamedStreamOpener implementtion.
            std::istream* openStream(const sk::util::Pathname& name) const;

          private:
            MockingTestFixture(const MockingTestFixture& other);
            MockingTestFixture& operator = (const MockingTestFixture& other);
        };
      }
    }
  }
}

#endif /* _SK_RT_CONFIG_TEST_MOCKINGTESTFIXTURE_ */
