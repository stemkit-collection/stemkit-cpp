/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "InspectTest.h"
#include <sk/util/inspect.h>
#include <sk/util/stl/inspect.h>

#include <vector>
#include <deque>
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::InspectTest);

sk::util::test::InspectTest::
InspectTest()
{
}

sk::util::test::InspectTest::
~InspectTest()
{
}

void
sk::util::test::InspectTest::
setUp()
{
}

void
sk::util::test::InspectTest::
tearDown()
{
}

void
sk::util::test::InspectTest::
testCharBuffers()
{
  CPPUNIT_ASSERT_EQUAL("<null>", sk::util::inspect(0, 0));
  CPPUNIT_ASSERT_EQUAL("<null>", sk::util::inspect(reinterpret_cast<const char*>(0)));
  CPPUNIT_ASSERT_EQUAL("\"abc\"", sk::util::inspect("abc"));
  CPPUNIT_ASSERT_EQUAL("\"abc\\x00\"", sk::util::inspect("abc", 4));
}

void
sk::util::test::InspectTest::
testStrings()
{
  sk::util::String s("abcd\n\r\005");
  sk::util::Object& o = s;

  CPPUNIT_ASSERT_EQUAL("\"abcd\\n\\r\\x05\"", sk::util::inspect(s));
  CPPUNIT_ASSERT_EQUAL("\"abcd\\n\\r\\x05\"", sk::util::inspect(o));
}

void 
sk::util::test::InspectTest::
testVectors()
{
  std::vector<sk::util::String> depot;
  CPPUNIT_ASSERT_EQUAL("[]", sk::util::inspect(depot));

  depot.push_back("aaa");
  depot.push_back("zzz");

  CPPUNIT_ASSERT_EQUAL("[2: 0=\"aaa\", 1=\"zzz\" ]", sk::util::inspect(depot));
}

void 
sk::util::test::InspectTest::
testLists()
{
  std::list<sk::util::String> depot;
  CPPUNIT_ASSERT_EQUAL("[]", sk::util::inspect(depot));

  depot.push_back("aaa");
  depot.push_back("zzz");

  CPPUNIT_ASSERT_EQUAL("[2: 0=\"aaa\", 1=\"zzz\" ]", sk::util::inspect(depot));
}

void 
sk::util::test::InspectTest::
testDeques()
{
  std::deque<sk::util::String> depot;
  CPPUNIT_ASSERT_EQUAL("[]", sk::util::inspect(depot));

  depot.push_back("aaa");
  depot.push_back("zzz");

  CPPUNIT_ASSERT_EQUAL("[2: 0=\"aaa\", 1=\"zzz\" ]", sk::util::inspect(depot));
}

void 
sk::util::test::InspectTest::
testContent()
{
  CPPUNIT_ASSERT_EQUAL("\"abcd\"", sk::util::inspect("abcd"));
  CPPUNIT_ASSERT_EQUAL("\"ab\\\"cd\"", sk::util::inspect("ab\"cd"));
  CPPUNIT_ASSERT_EQUAL("\"ab\\\\cd\"", sk::util::inspect("ab\\cd"));
}
