/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/


#include "XmlProcessorTest.h"
#include "../XmlProcessor.h"

#include <sk/util/Holder.cxx>
#include <sk/rt/scope/Aggregator.h>
#include <sk/rt/logger/Level.h>
#include <sk/other/tinyxml/tinyxml.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::scope::test::XmlProcessorTest);

sk::rt::scope::test::XmlProcessorTest::
XmlProcessorTest()
{
}

sk::rt::scope::test::XmlProcessorTest::
~XmlProcessorTest()
{
}

void
sk::rt::scope::test::XmlProcessorTest::
setUp()
{
  _aggregatorHolder.set(new Aggregator);
}

void
sk::rt::scope::test::XmlProcessorTest::
tearDown()
{
  _aggregatorHolder.clear();
}

void
sk::rt::scope::test::XmlProcessorTest::
testEmpty()
{
  XmlProcessor processor("", "a/b/c", _aggregatorHolder.getMutable(), std::map<std::string, std::string>());
  CPPUNIT_ASSERT_EQUAL("a/b/c", processor.getLocation().toString());
  CPPUNIT_ASSERT(processor.findScopeElement(processor.getHandle()) == 0);
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopOnly()
{
  XmlProcessor processor("<scope id='a' /><scope name='aaa' id='b' />", "a/b/c", _aggregatorHolder.getMutable(), std::map<std::string, std::string>());
  CPPUNIT_ASSERT_EQUAL("a/b/c", processor.getLocation().toString());

  TiXmlElement* unnamed_scope = processor.findScopeElement(processor.getHandle());
  TiXmlElement* named_scope = processor.findScopeElement(processor.getHandle(), "aaa");

  CPPUNIT_ASSERT(unnamed_scope != 0);
  CPPUNIT_ASSERT(named_scope != 0);

  CPPUNIT_ASSERT_EQUAL("a", unnamed_scope->Attribute("id"));
  CPPUNIT_ASSERT_EQUAL("b", named_scope->Attribute("id"));
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopLogInfo()
{
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogObject());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.getMutable().obtain("aaa").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogPid());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_NOTICE));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_INFO));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_WARNING));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_ERROR));

  XmlProcessor processor("<scope name='app'><log show-time='true'><level severity='warning'/></log></scope>", "a/b/c", _aggregatorHolder.getMutable(), std::map<std::string, std::string>());
  processor.start(sk::util::Strings("app"));

  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogObject());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.getMutable().obtain("aaa").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogPid());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.getMutable().obtain("bbb").getConfig().checkLogLevel(logger::Level::SK_L_WARNING));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.getMutable().obtain("bbb").getConfig().checkLogLevel(logger::Level::SK_L_ERROR));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_NOTICE));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::SK_L_INFO));
}

void
sk::rt::scope::test::XmlProcessorTest::
testValueSubstituion()
{
  std::map<std::string, std::string> values;
  values["port"] = "2222";
  values["prefix"] = "my";

  XmlProcessor processor(
    "<scope name='top-app'>\
      <property name='#{prefix}-location' value='log-#{port}' />\
      <property name='name' value='zzz-#{aaa}-bbb' />\
      <property name='abc' value='uuu-#{scope}-ooo' />\
      <property name='multi' value='#{prefix}-v-#{port}-end' />\
    ", "a/b/c", _aggregatorHolder.getMutable(), values
  );
  processor.start(sk::util::Strings());

  CPPUNIT_ASSERT_EQUAL("log-2222", _aggregatorHolder.get().getConfig().getProperty("my-location"));
  CPPUNIT_ASSERT_EQUAL("zzz--bbb", _aggregatorHolder.get().getConfig().getProperty("name"));
  CPPUNIT_ASSERT_EQUAL("uuu-top-app-ooo", _aggregatorHolder.get().getConfig().getProperty("abc"));
  CPPUNIT_ASSERT_EQUAL("my-v-2222-end", _aggregatorHolder.get().getConfig().getProperty("multi"));
}
