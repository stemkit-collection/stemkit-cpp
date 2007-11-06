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
  XmlProcessor processor("", "a/b/c", _aggregatorHolder.get());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c").inspect(), processor.getLocation().inspect());
  CPPUNIT_ASSERT(processor.getHandle().FirstChild().ToElement() == 0);
}

void
sk::rt::scope::test::XmlProcessorTest::
testTopOnly()
{
  XmlProcessor processor("<test-app/>", "a/b/c", _aggregatorHolder.get());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("a/b/c").inspect(), processor.getLocation().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("test-app").inspect(), sk::util::String(processor.getHandle().FirstChild().ToNode()->Value()).inspect());
}
