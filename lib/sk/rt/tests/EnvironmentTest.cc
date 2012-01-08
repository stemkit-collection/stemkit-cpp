/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "EnvironmentTest.h"
#include <sk/rt/Environment.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::EnvironmentTest);

sk::rt::tests::EnvironmentTest::
EnvironmentTest()
{
}

sk::rt::tests::EnvironmentTest::
~EnvironmentTest()
{
}

void
sk::rt::tests::EnvironmentTest::
setUp()
{
}

void
sk::rt::tests::EnvironmentTest::
tearDown()
{
}

void
sk::rt::tests::EnvironmentTest::
testBasics()
{
  sk::rt::Environment environment;
  CPPUNIT_ASSERT(environment.size() > 0);
}

void
sk::rt::tests::EnvironmentTest::
testSerializeEmpty()
{
  sk::util::Properties registry;
  sk::rt::Environment environment(registry);
  CPPUNIT_ASSERT_EQUAL(0, environment.size());

  std::vector<char> block;
  std::vector<char*> references = environment.serialize(block);

  CPPUNIT_ASSERT_EQUAL(1, int(block.size()));
  CPPUNIT_ASSERT_EQUAL('\0', block.at(0));

  CPPUNIT_ASSERT_EQUAL(1, int(references.size()));
  CPPUNIT_ASSERT_EQUAL(0, references.at(0));
}

#include <sk/util/inspect.h>

void
sk::rt::tests::EnvironmentTest::
testSerializeContent()
{
  sk::util::Properties registry;
  registry.setProperty("aaa", "abc");
  registry.setProperty("bbb", 18);

  sk::rt::Environment environment(registry);
  CPPUNIT_ASSERT_EQUAL(2, environment.size());

  CPPUNIT_ASSERT_EQUAL("abc", environment.getProperty("aaa"));
  CPPUNIT_ASSERT_EQUAL("18", environment.getProperty("bbb"));

  std::vector<char> block;
  const std::vector<char*> references = environment.serialize(block);
  CPPUNIT_ASSERT_EQUAL("\"aaa=abc\\x00bbb=18\\x00\\x00\"", sk::util::inspect(block));

  CPPUNIT_ASSERT_EQUAL(3, int(references.size()));
  CPPUNIT_ASSERT_EQUAL(reinterpret_cast<void*>(&block.at(0)), reinterpret_cast<void*>(references.at(0)));
  CPPUNIT_ASSERT_EQUAL(reinterpret_cast<void*>(&block.at(8)), reinterpret_cast<void*>(references.at(1)));
  CPPUNIT_ASSERT_EQUAL(reinterpret_cast<void*>(0), reinterpret_cast<void*>(references.at(2)));

  CPPUNIT_ASSERT_EQUAL("aaa=abc", references.at(0));
  CPPUNIT_ASSERT_EQUAL("bbb=18", references.at(1));
}
