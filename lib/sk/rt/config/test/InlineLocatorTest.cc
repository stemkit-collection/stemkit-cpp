/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "InlineLocatorTest.h"
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/config/StreamProcessor.h>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::config::test::InlineLocatorTest);

sk::rt::config::test::InlineLocatorTest::
InlineLocatorTest()
{
}

sk::rt::config::test::InlineLocatorTest::
~InlineLocatorTest()
{
}

namespace {
  struct Processor : public virtual sk::rt::config::StreamProcessor {
    Processor(std::vector<sk::util::String>& locations, sk::util::String& content)
      : _locations(locations), _content(content) {}

    void process(std::istream& stream, const sk::util::Pathname& location) const {
      std::string line;
      _content = ":";
      while(std::getline(stream, line)) {
        _content += line + ':';
      }
      _locations.push_back(location.toString());
    }
    std::vector<sk::util::String>& _locations;
    sk::util::String& _content;
  };
}

void
sk::rt::config::test::InlineLocatorTest::
testStandAlone()
{
  InlineLocator locator("he-he-he\nand\nbe-be-be");
  std::vector<sk::util::String> locations;
  sk::util::String content;

  locator.invoke(Processor(locations, content));

  CPPUNIT_ASSERT_EQUAL(size_t(1), locations.size());
  CPPUNIT_ASSERT_EQUAL(".", locations.at(0));
  CPPUNIT_ASSERT_EQUAL(":he-he-he:and:be-be-be:", content);
}
