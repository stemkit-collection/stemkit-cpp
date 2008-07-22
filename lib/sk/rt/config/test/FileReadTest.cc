/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "FileReadTest.h"
#include <sk/rt/config/CwdUprootLocator.h>
#include <sk/rt/config/StreamProcessor.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::config::test::FileReadTest);

sk::rt::config::test::FileReadTest::
FileReadTest()
{
}

sk::rt::config::test::FileReadTest::
~FileReadTest()
{
}

void
sk::rt::config::test::FileReadTest::
setUp()
{
}

void
sk::rt::config::test::FileReadTest::
tearDown()
{
}

namespace {
  struct Processor : public virtual sk::rt::config::StreamProcessor {
    Processor(std::vector<sk::util::String>& content, std::vector<sk::util::String>& locations)
      : _content(content), _locations(locations) {}

    void process(std::istream& stream, const sk::util::String& location) const {
      std::string line;
      while(getline(stream, line).eof() == false) {
        _content.push_back(line);
      }
      _locations.push_back(location);
    }
    std::vector<sk::util::String>& _content;
    std::vector<sk::util::String>& _locations;
  };
}

void
sk::rt::config::test::FileReadTest::
testReadPasswdFromCwd()
{
  CwdUprootLocator locator("src/config/Jam.project.gcc");

  std::vector<sk::util::String> content;
  std::vector<sk::util::String> locations;

  locator.invoke(Processor(content, locations));

  CPPUNIT_ASSERT_EQUAL(size_t(1), locations.size());
  CPPUNIT_ASSERT(content.size() > 5);
}
