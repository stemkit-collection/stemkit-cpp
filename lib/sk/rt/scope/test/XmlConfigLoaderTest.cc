/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "XmlConfigLoaderTest.h"
#include "../XmlConfigLoader.h"
#include <sk/rt/scope/Aggregator.h>
#include <sk/util/Holder.cxx>

#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::scope::test::XmlConfigLoaderTest);

sk::rt::scope::test::XmlConfigLoaderTest::
XmlConfigLoaderTest()
{
}

sk::rt::scope::test::XmlConfigLoaderTest::
~XmlConfigLoaderTest()
{
}

void
sk::rt::scope::test::XmlConfigLoaderTest::
setUp()
{
  _aggregatorHolder.set(new Aggregator);
}

void
sk::rt::scope::test::XmlConfigLoaderTest::
tearDown()
{
  _aggregatorHolder.clear();
}

sk::rt::scope::Aggregator&
sk::rt::scope::test::XmlConfigLoaderTest::
aggregator() 
{
  return _aggregatorHolder.get();
}

void
sk::rt::scope::test::XmlConfigLoaderTest::
testSimple()
{
  XmlConfigLoader loader("app", aggregator());
  std::stringstream stream;
  stream << 
    "<scope name='app'>\n" 
    "  <log>\n"
    "    <level severity='none' />\n"
    "  </log>\n"
    "  <scope name='zzz'>\n"
    "    <log show-time='true'>\n"
    "      <level severity='notice' />\n"
    "    </log>\n"
    "  </scope>\n"
    "</scope>\n"
  ;
  loader.process(stream, "/a/b/c");

  CPPUNIT_ASSERT_EQUAL(true, aggregator().obtain("zzz").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, aggregator().getConfig().isLogTime());
}
