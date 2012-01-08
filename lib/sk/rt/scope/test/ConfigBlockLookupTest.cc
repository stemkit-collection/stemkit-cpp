/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "ConfigBlockLookupTest.h"
#include <sk/util/Holder.cxx>
#include <../XmlProcessor.h>
#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/logger/Level.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::scope::test::ConfigBlockLookupTest);

sk::rt::scope::test::ConfigBlockLookupTest::
ConfigBlockLookupTest()
{
}

sk::rt::scope::test::ConfigBlockLookupTest::
~ConfigBlockLookupTest()
{
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
setUp()
{
  _aggregatorHolder.set(new Aggregator);
  _processorHolder.set(
    new XmlProcessor(
      "\n\
        <scope name='aaa'>\n\
          <property name='attr' value='zzz-#{scope}' />\n\
        </scope>\n\
        \n\
        <scope>\n\
          <property name='attr' value='uuu-#{scope}' />\n\
        </scope>\n\
      ",
      "/config/abc",
      _aggregatorHolder.getMutable(),
      std::map<std::string, std::string>()
    )
  );
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
tearDown()
{
  _processorHolder.clear();
  _aggregatorHolder.clear();
}

sk::rt::scope::XmlProcessor&
sk::rt::scope::test::ConfigBlockLookupTest::
processor()
{
  return _processorHolder.getMutable();
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
testExactMatch()
{
  processor().start(sk::util::Strings("aaa"));
  CPPUNIT_ASSERT_EQUAL("zzz-aaa", _aggregatorHolder.get().getConfig().getProperty("attr", "ddd"));
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
testRequestingEmptyGetsFirst()
{
  processor().start(sk::util::Strings());
  CPPUNIT_ASSERT_EQUAL("zzz-aaa", _aggregatorHolder.get().getConfig().getProperty("attr", "ddd"));
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
testNonExistentGetsDefault()
{
  processor().start(sk::util::Strings("s1"));
  CPPUNIT_ASSERT_EQUAL("uuu-s1", _aggregatorHolder.get().getConfig().getProperty("attr", "ddd"));
}

void
sk::rt::scope::test::ConfigBlockLookupTest::
testNonExistentAndNoDefault()
{
  _processorHolder.set(new XmlProcessor(
    "\n\
      <scope name='abc'> \n\
        <property name='attr' value='ooo' />\n\
      </scope>\n\
    ",
    "",
    _aggregatorHolder.getMutable(),
    std::map<std::string, std::string>())
  );
  processor().start(sk::util::Strings("some"));
  CPPUNIT_ASSERT_EQUAL("none", _aggregatorHolder.get().getConfig().getProperty("attr", "none"));
}
