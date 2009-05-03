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

    void process(std::istream& stream, const sk::util::Pathname& location) const {
      std::string line;
      while(getline(stream, line).eof() == false) {
        _content.push_back(line);
      }
      _locations.push_back(location.toString());
    }
    std::vector<sk::util::String>& _content;
    std::vector<sk::util::String>& _locations;
  };
}

void
sk::rt::config::test::FileReadTest::
testReadFileFromCwd()
{
  CwdUprootLocator locator("src/config/Jam.project");

  std::vector<sk::util::String> content;
  std::vector<sk::util::String> locations;

  locator.invoke(Processor(content, locations));

  // It can find more that one file in case of multi-platfrom build when
  // folder 'platforms' is created parallel to 'src' and the latter is
  // symbolically linked to at particular platform 'src' under 'platforms'.
  //
  CPPUNIT_ASSERT(locations.size() >= 1);
  CPPUNIT_ASSERT_EQUAL(3 * locations.size(), content.size());
}
