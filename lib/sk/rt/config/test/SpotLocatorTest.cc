/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "SpotLocatorTest.h"
#include <sk/rt/config/SpotLocator.h>
#include <sk/rt/config/StreamProcessor.h>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::config::test::SpotLocatorTest);

sk::rt::config::test::SpotLocatorTest::
SpotLocatorTest()
{
}

sk::rt::config::test::SpotLocatorTest::
~SpotLocatorTest()
{
}

void
sk::rt::config::test::SpotLocatorTest::
setUp()
{
}

void
sk::rt::config::test::SpotLocatorTest::
tearDown()
{
}

namespace {
  struct Processor : public virtual sk::rt::config::StreamProcessor {
    Processor(std::vector<sk::util::String>& locations)
      : _locations(locations) {}

    void process(std::istream& stream, const sk::util::String& location) const {
      _locations.push_back(location);
    }
    std::vector<sk::util::String>& _locations;
  };
}

void
sk::rt::config::test::SpotLocatorTest::
testStandAlone()
{
  SpotLocator locator("abc", "a/b/c");
  std::vector<sk::util::String> locations;

  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(1), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c"), locations.at(0));
}

void
sk::rt::config::test::SpotLocatorTest::
testCascading()
{
  SpotLocator locator("a/b", SpotLocator("c/d", SpotLocator("abc", "e/z")));
  std::vector<sk::util::String> locations;

  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(3), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("e/z"), locations.at(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("c/d"), locations.at(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b"), locations.at(2));
}
