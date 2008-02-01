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
#include <sk/rt/logger/DirectFileDestination.h>
#include <other/tinyxml/tinyxml.h>

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
  XmlProcessor processor("", "a/b/c", _aggregatorHolder.get(), std::map<std::string, std::string>());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c").inspect(), processor.getLocation().inspect());
  CPPUNIT_ASSERT(processor.findScopeElement(processor.getHandle()) == 0);
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopOnly()
{
  XmlProcessor processor("<scope id='a' /><scope name='aaa' id='b' />", "a/b/c", _aggregatorHolder.get(), std::map<std::string, std::string>());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c").inspect(), processor.getLocation().inspect());

  TiXmlElement* unnamed_scope = processor.findScopeElement(processor.getHandle());
  TiXmlElement* named_scope = processor.findScopeElement(processor.getHandle(), "aaa");

  CPPUNIT_ASSERT(unnamed_scope != 0);
  CPPUNIT_ASSERT(named_scope != 0);

  CPPUNIT_ASSERT_EQUAL(sk::util::String("a").inspect(), sk::util::String(unnamed_scope->Attribute("id")).inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("b").inspect(), sk::util::String(named_scope->Attribute("id")).inspect());
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopLogInfo()
{
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogObject());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().obtain("aaa").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogPid());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::NOTICE));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::INFO));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::WARNING));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::ERROR));

  XmlProcessor processor("<scope name='app'><log show-time='true'><level severity='warning'/></log></scope>", "a/b/c", _aggregatorHolder.get(), std::map<std::string, std::string>());
  processor.start("app");

  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogObject());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("aaa").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogPid());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("bbb").getConfig().checkLogLevel(logger::Level::WARNING));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("bbb").getConfig().checkLogLevel(logger::Level::ERROR));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::NOTICE));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::INFO));
}

void
sk::rt::scope::test::XmlProcessorTest::
testValueSubstituion()
{
  std::map<std::string, std::string> values;
  values["port"] = "2222";

  XmlProcessor processor(
    "<scope name='app'>\
        <log destination='file' >\
          <file location='log-#{port}' name='zzz-#{aaa}-bbb' />\
        </log>\
     </scope>\
    ", "a/b/c", _aggregatorHolder.get(), values
  );
  processor.start("app");

  logger::Destination& destination = _aggregatorHolder.get().getConfig().getLogDestination();
  logger::DirectFileDestination& file = dynamic_cast<logger::DirectFileDestination&>(destination);

  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c/log-2222"), file.getPathname().dirname());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("zzz--bbb.log"), file.getPathname().basename());
}
