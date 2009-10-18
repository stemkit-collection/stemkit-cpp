/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Holder.cxx>
#include <sk/util/Container.h>
#include "StringNodeTest.h"
#include "../StringNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::StringNodeTest);

sk::util::pp::test::StringNodeTest::
StringNodeTest()
{
}

sk::util::pp::test::StringNodeTest::
~StringNodeTest()
{
}

void
sk::util::pp::test::StringNodeTest::
setUp()
{
}

void
sk::util::pp::test::StringNodeTest::
tearDown()
{
}

void
sk::util::pp::test::StringNodeTest::
testNone()
{
  CPPUNIT_ASSERT(StringNode().parse(sk::util::Container(""), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(StringNode().parse(sk::util::Container("."), 0, sk::util::Container("[*.")) == 0);
  CPPUNIT_ASSERT(StringNode().parse(sk::util::Container("\"abcd"), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(StringNode().parse(sk::util::Container("\"abcd\\\""), 0, sk::util::Container()) == 0);
}

void
sk::util::pp::test::StringNodeTest::
testQuotedOnly()
{
  sk::util::Holder<Node> nodeHolder(StringNode().parse(sk::util::Container("    \"hello \\\"world\\\"\""),  4, sk::util::Container()));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);

  CPPUNIT_ASSERT_EQUAL("\"hello \\\"world\\\"\"", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(4, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(21, nodeHolder.get().endPosition());
}

void 
sk::util::pp::test::StringNodeTest::
testQuotedThenRegularUpto()
{
  sk::util::Holder<Node> nodeHolder(StringNode().parse(sk::util::Container("me\"abc\".zzz<uuu"),  0, sk::util::Container("=<(")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);

  CPPUNIT_ASSERT_EQUAL("me\"abc\".zzz", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(11, nodeHolder.get().endPosition());
}
void 
sk::util::pp::test::StringNodeTest::
testQuotedThenRegular()
{
  sk::util::Holder<Node> nodeHolder(StringNode().parse(sk::util::Container("\"abc\".zzz"),  0, sk::util::Container()));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);

  CPPUNIT_ASSERT_EQUAL("\"abc\".zzz", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(9, nodeHolder.get().endPosition());
}
