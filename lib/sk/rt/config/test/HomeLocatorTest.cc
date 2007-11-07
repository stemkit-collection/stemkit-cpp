/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "HomeLocatorTest.h"
#include <sk/rt/config/HomeLocator.h>
#include <sk/rt/config/StreamProcessor.h>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::config::test::HomeLocatorTest);

sk::rt::config::test::HomeLocatorTest::
HomeLocatorTest()
{
}

sk::rt::config::test::HomeLocatorTest::
~HomeLocatorTest()
{
}

namespace {
  struct Processor : public virtual sk::rt::config::StreamProcessor {
    Processor(std::vector<sk::util::String>& locations, std::vector<sk::util::String>& streams)
      : _locations(locations), _streams(streams) {}

    void process(std::istream& stream, const sk::util::String& location) const {
      sk::util::String content;
      stream >> content;

      _locations.push_back(location);
      _streams.push_back(content);
    }
    std::vector<sk::util::String>& _locations;
    std::vector<sk::util::String>& _streams;
  };
}

void
sk::rt::config::test::HomeLocatorTest::
testStandAlone()
{
  HomeLocator locator(".abcrc");
  std::vector<sk::util::String> locations;
  std::vector<sk::util::String> streams;
  locator.invoke(Processor(locations, streams));

  CPPUNIT_ASSERT_EQUAL(size_t(1), locations.size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), streams.size());

  CPPUNIT_ASSERT_EQUAL(sk::util::String(getenv("HOME")).inspect(), locations.at(0).inspect());
  CPPUNIT_ASSERT_EQUAL((sk::util::String(getenv("HOME")) + "/.abcrc").inspect(), streams.at(0).inspect());
}