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
  XmlProcessor processor("", "a/b/c", _aggregatorHolder.get(), sk::util::StringHash());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c").inspect(), processor.getLocation().inspect());
  CPPUNIT_ASSERT(processor.findScopeElement(processor.getHandle()) == 0);
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopOnly()
{
  XmlProcessor processor("<scope id='a' /><scope name='aaa' id='b' />", "a/b/c", _aggregatorHolder.get(), sk::util::StringHash());
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

  XmlProcessor processor("<scope name='app'><log show-time='true'><level severity='warning'/></log></scope>", "a/b/c", _aggregatorHolder.get(), sk::util::StringHash());
  processor.start("app");

  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogObject());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("aaa").getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().isLogPid());
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("bbb").getConfig().checkLogLevel(logger::Level::WARNING));
  CPPUNIT_ASSERT_EQUAL(true, _aggregatorHolder.get().obtain("bbb").getConfig().checkLogLevel(logger::Level::ERROR));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::NOTICE));
  CPPUNIT_ASSERT_EQUAL(false, _aggregatorHolder.get().getConfig().checkLogLevel(logger::Level::INFO));
}
