/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "XmlConfigLoaderTest.h"
#include "../XmlConfigLoader.h"
#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/logger/Level.h>
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
testBigPicture()
{
  XmlConfigLoader loader("app", aggregator(), sk::util::StringHash());
  std::stringstream stream;
  stream << 
    "<scope name='app'>\n" 
    "  <log>\n"
    "    <level severity='warning' />\n"
    "  </log>\n"
    "  <property name='p1' value='ub2' />\n"
    "  <property name='p2' value='219' />\n"
    "  <scope name='zzz'>\n"
    "    <log show-time='true' level='info' />\n"
    "    <property name='p1'>\n"
    "      Hello,\n"
    "      World.\n"
    "    </property>\n"
    "  </scope>\n"
    "</scope>\n"
  ;
  loader.process(stream, "/a/b/c");

  CPPUNIT_ASSERT_EQUAL(true, aggregator().obtain("zzz").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(true, aggregator().obtain("zzz").obtain("abc").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, aggregator().getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, aggregator().obtain("uuu").getConfig().isLogTime());

  CPPUNIT_ASSERT_EQUAL(sk::util::String("ub2").inspect(), aggregator().getConfig().getProperty("p1").inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("219").inspect(), aggregator().getConfig().getProperty("p2").inspect());
  CPPUNIT_ASSERT_EQUAL(219, aggregator().getConfig().getProperty("p2", 0));
  CPPUNIT_ASSERT_EQUAL(17, aggregator().getConfig().getProperty("p1", 17));
  CPPUNIT_ASSERT_EQUAL(19, aggregator().getConfig().getProperty("p3", 19));

  CPPUNIT_ASSERT_EQUAL(sk::util::String("Hello, World.").inspect(), aggregator().obtain("zzz").getConfig().getProperty("p1").inspect());

  CPPUNIT_ASSERT_EQUAL(true, aggregator().getConfig().checkLogLevel(logger::Level::ERROR));
  CPPUNIT_ASSERT_EQUAL(true, aggregator().getConfig().checkLogLevel(logger::Level::WARNING));
  CPPUNIT_ASSERT_EQUAL(false, aggregator().getConfig().checkLogLevel(logger::Level::NOTICE));

  CPPUNIT_ASSERT_EQUAL(true, aggregator().obtain("zzz").getConfig().checkLogLevel(logger::Level::INFO));
  CPPUNIT_ASSERT_EQUAL(true, aggregator().obtain("zzz").getConfig().checkLogLevel(logger::Level::INFO));
  CPPUNIT_ASSERT_EQUAL(false, aggregator().obtain("zzz").getConfig().checkLogLevel(logger::Level::DETAIL));
}
