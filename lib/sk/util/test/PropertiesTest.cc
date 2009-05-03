/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "PropertiesTest.h"
#include <sk/util/Properties.h>
#include <sk/util/NoSuchElementException.h>
#include <sk/util/IllegalArgumentException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PropertiesTest);

sk::util::test::PropertiesTest::
PropertiesTest()
{
}

sk::util::test::PropertiesTest::
~PropertiesTest()
{
}

void
sk::util::test::PropertiesTest::
setUp()
{
}

void
sk::util::test::PropertiesTest::
tearDown()
{
}

void
sk::util::test::PropertiesTest::
testBasics()
{
  sk::util::Properties registry;

  CPPUNIT_ASSERT_EQUAL(0, registry.size());

  registry.setProperty("aaa", "bbb");
  CPPUNIT_ASSERT_EQUAL(1, registry.size());
  CPPUNIT_ASSERT(registry.hasProperty("aaa") == true);
  CPPUNIT_ASSERT(registry.hasProperty("bbb") == false);
  CPPUNIT_ASSERT_EQUAL("bbb", registry.getProperty("aaa"));

  registry.setProperty("aaa", "ccc");
  CPPUNIT_ASSERT_EQUAL(1, registry.size());
  CPPUNIT_ASSERT(registry.hasProperty("aaa") == true);
  CPPUNIT_ASSERT(registry.hasProperty("bbb") == false);
  CPPUNIT_ASSERT_EQUAL("ccc", registry.getProperty("aaa"));

  registry.setProperty("bbb", "zzz");
  CPPUNIT_ASSERT_EQUAL(2, registry.size());
  CPPUNIT_ASSERT(registry.hasProperty("aaa") == true);
  CPPUNIT_ASSERT(registry.hasProperty("bbb") == true);
  CPPUNIT_ASSERT_EQUAL("ccc", registry.getProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("zzz", registry.getProperty("bbb"));

  CPPUNIT_ASSERT_THROW(registry.getProperty("ccc"), sk::util::NoSuchElementException);

  registry.clear();
  CPPUNIT_ASSERT_EQUAL(0, registry.size());
}

void
sk::util::test::PropertiesTest::
testGetWithDefaults()
{
  sk::util::Properties registry;

  registry.setProperty("aaa", "abc");
  registry.setProperty("bbb", "15");
  registry.setProperty("b1", "true");
  registry.setProperty("b2", "yes");
  registry.setProperty("b3", "false");

  CPPUNIT_ASSERT_EQUAL("abc", registry.getProperty("aaa", "uuu"));
  CPPUNIT_ASSERT_EQUAL("uuu", registry.getProperty("ccc", "uuu"));

  CPPUNIT_ASSERT_EQUAL(15, registry.getProperty("bbb", 29));
  CPPUNIT_ASSERT_EQUAL(29, registry.getProperty("ccc", 29));
  CPPUNIT_ASSERT_EQUAL(31, registry.getProperty("aaa", 31));

  CPPUNIT_ASSERT_EQUAL(true, registry.getProperty("b1", sk::util::Boolean::B_FALSE));
  CPPUNIT_ASSERT_EQUAL(true, registry.getProperty("b2", sk::util::Boolean::B_FALSE));
  CPPUNIT_ASSERT_EQUAL(false, registry.getProperty("b3", sk::util::Boolean::B_TRUE));
}

void
sk::util::test::PropertiesTest::
testSetKinds()
{
  sk::util::Properties registry;

  registry.setProperty("number", 279);
  registry.setProperty("b_true", sk::util::Boolean::B_TRUE);
  registry.setProperty("b_false", sk::util::Boolean::B_FALSE);

  CPPUNIT_ASSERT_EQUAL("279", registry.getProperty("number"));
  CPPUNIT_ASSERT_EQUAL("true", registry.getProperty("b_true"));
  CPPUNIT_ASSERT_EQUAL("false", registry.getProperty("b_false"));
}

void
sk::util::test::PropertiesTest::
testDump()
{
  sk::util::Properties registry;

  registry.setProperty("aaa", "zzz");
  registry.setProperty("bbb", 512);

  CPPUNIT_ASSERT_EQUAL("aaa=zzz", registry.dumpProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("bbb=512", registry.dumpProperty("bbb"));
  CPPUNIT_ASSERT_THROW(registry.dumpProperty("ccc"), sk::util::NoSuchElementException);
}

void
sk::util::test::PropertiesTest::
testDelete()
{
  sk::util::Properties registry;

  registry.setProperty("aaa", "abc");
  registry.setProperty("bbb", "zzzzz");
  registry.setProperty("ccc", "uuu");

  CPPUNIT_ASSERT_EQUAL(3, registry.size());

  CPPUNIT_ASSERT(registry.deleteProperty("bbb") == true);
  CPPUNIT_ASSERT_EQUAL(2, registry.size());

  CPPUNIT_ASSERT(registry.deleteProperty("dddd") == false);
  CPPUNIT_ASSERT_EQUAL(2, registry.size());

  CPPUNIT_ASSERT(registry.deleteProperty("aaa") == true);
  CPPUNIT_ASSERT_EQUAL(1, registry.size());

  CPPUNIT_ASSERT(registry.deleteProperty("ccc") == true);
  CPPUNIT_ASSERT_EQUAL(0, registry.size());

  CPPUNIT_ASSERT(registry.deleteProperty("aaa") == false);
  CPPUNIT_ASSERT(registry.deleteProperty("bbb") == false);
  CPPUNIT_ASSERT(registry.deleteProperty("ccc") == false);
}

namespace {
  struct Propagator : public virtual sk::util::BinaryProcessor<const sk::util::String, const sk::util::String> {
    Propagator(sk::util::PropertyRegistry& registry)
      : _registry(registry) {}

    void process(const sk::util::String& key, const sk::util::String& value) const {
      _registry.setProperty(key, value);
    }

    sk::util::PropertyRegistry& _registry;
  };
}

void
sk::util::test::PropertiesTest::
testForEach()
{
  sk::util::Properties registry;

  registry.setProperty("aaa", "zzz");
  registry.setProperty("bbb", 17);
  registry.setProperty("ccc", sk::util::Boolean::B_TRUE);
  registry.setProperty("ddd", sk::util::Boolean::B_FALSE);

  sk::util::Properties result;
  CPPUNIT_ASSERT_EQUAL(0, result.size());
  registry.forEach(Propagator(result));

  CPPUNIT_ASSERT_EQUAL(4, result.size());
  CPPUNIT_ASSERT_EQUAL("zzz", result.getProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("17", result.getProperty("bbb"));
  CPPUNIT_ASSERT_EQUAL("true", result.getProperty("ccc"));
  CPPUNIT_ASSERT_EQUAL("false", result.getProperty("ddd"));
}

void
sk::util::test::PropertiesTest::
testParseAndInspect()
{
  sk::util::Properties registry;
  CPPUNIT_ASSERT_EQUAL("{}", registry.inspect());

  CPPUNIT_ASSERT_EQUAL(0, registry.size());
  registry.parseProperty("aaa=abcd");
  CPPUNIT_ASSERT_EQUAL(1, registry.size());
  CPPUNIT_ASSERT_EQUAL("abcd", registry.getProperty("aaa"));

  registry.parseProperty("  aaa   = zzz ");
  CPPUNIT_ASSERT_EQUAL(1, registry.size());
  CPPUNIT_ASSERT_EQUAL(" zzz ", registry.getProperty("aaa"));

  registry.parseProperty(" bbb    =124");
  CPPUNIT_ASSERT_EQUAL(2, registry.size());
  CPPUNIT_ASSERT_EQUAL("124", registry.getProperty("bbb"));

  CPPUNIT_ASSERT_THROW(registry.parseProperty("zzzzzzzzz"), sk::util::IllegalArgumentException);

  CPPUNIT_ASSERT_EQUAL("{ aaa => \" zzz \", bbb => \"124\" }", registry.inspect());
}

void 
sk::util::test::PropertiesTest::
testCopyConstructor()
{
  sk::util::Properties registry;
  registry.setProperty("aaa", "zzz");
  registry.setProperty("bbb", "u1");

  sk::util::Properties other(registry);
  CPPUNIT_ASSERT_EQUAL(2, other.size());
  CPPUNIT_ASSERT_EQUAL("zzz", other.getProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("u1", other.getProperty("bbb"));
}

void 
sk::util::test::PropertiesTest::
testCopyRegistry()
{
  sk::util::Properties source;
  source.setProperty("aaa", "zzz");
  source.setProperty("bbb", "u1");

  sk::util::PropertyRegistry& registry = source;
  sk::util::Properties other(registry);
  CPPUNIT_ASSERT_EQUAL(2, other.size());
  CPPUNIT_ASSERT_EQUAL("zzz", other.getProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("u1", other.getProperty("bbb"));
}
