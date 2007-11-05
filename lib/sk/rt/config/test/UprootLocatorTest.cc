/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "UprootLocatorTest.h"
#include <sk/rt/config/UprootLocator.h>
#include <sk/rt/config/StreamProcessor.h>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::config::test::UprootLocatorTest);

sk::rt::config::test::UprootLocatorTest::
UprootLocatorTest()
{
}

sk::rt::config::test::UprootLocatorTest::
~UprootLocatorTest()
{
}

void
sk::rt::config::test::UprootLocatorTest::
setUp()
{
}

void
sk::rt::config::test::UprootLocatorTest::
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
sk::rt::config::test::UprootLocatorTest::
testOneLevel()
{
  UprootLocator locator("ttt", "uuu");
  std::vector<sk::util::String> locations;
  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(1), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("uuu"), locations.at(0));
}

void
sk::rt::config::test::UprootLocatorTest::
testOneLevelCascading()
{
  UprootLocator locator("abc", "a", SpotLocator("zzz", "/u"));
  std::vector<sk::util::String> locations;
  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(2), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("/u"), locations.at(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a"), locations.at(1));
}

void
sk::rt::config::test::UprootLocatorTest::
testMultiLevel()
{
  UprootLocator locator("zzz", "a/b/c");
  std::vector<sk::util::String> locations;
  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(3), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a"), locations.at(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b"), locations.at(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c"), locations.at(2));
}

void
sk::rt::config::test::UprootLocatorTest::
testMultiLevelCascading()
{
  UprootLocator locator("abc", "a/b/c", SpotLocator("zzz", "/u"));
  std::vector<sk::util::String> locations;
  locator.invoke(Processor(locations), true);

  CPPUNIT_ASSERT_EQUAL(size_t(4), locations.size());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("/u"), locations.at(0));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a"), locations.at(1));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b"), locations.at(2));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c"), locations.at(3));
}
