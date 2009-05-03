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

