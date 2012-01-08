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
#include "HolderNodeTest.h"
#include "../HolderNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::HolderNodeTest);

sk::util::pp::test::HolderNodeTest::
HolderNodeTest()
{
}

sk::util::pp::test::HolderNodeTest::
~HolderNodeTest()
{
}

void
sk::util::pp::test::HolderNodeTest::
setUp()
{
}

void
sk::util::pp::test::HolderNodeTest::
tearDown()
{
}

void
sk::util::pp::test::HolderNodeTest::
testNone()
{
  CPPUNIT_ASSERT(HolderNode().parse(sk::util::Container("("), 0, sk::util::Container("")) == 0);
}

void
sk::util::pp::test::HolderNodeTest::
testEmpty()
{
  sk::util::Holder<Node> nodeHolder(HolderNode().parse(sk::util::Container("( )"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(3, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<HolderNode: empty>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::HolderNodeTest::
testHoldPointer()
{
  sk::util::Holder<Node> nodeHolder(HolderNode().parse(sk::util::Container("(*<null>)"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(9, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<HolderNode: *<PointerNode: <null>>>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::HolderNodeTest::
testHoldText()
{
  sk::util::Holder<Node> nodeHolder(HolderNode().parse(sk::util::Container("(&HELLO)"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(8, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<HolderNode: &<TextNode: \"HELLO\">>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::HolderNodeTest::
testHoldQuotedText()
{
  sk::util::Holder<Node> nodeHolder(HolderNode().parse(sk::util::Container("(&\"world\")"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(10, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<HolderNode: &<TextNode: \"\\\"world\\\"\">>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::HolderNodeTest::
testHoldHolder()
{
  sk::util::Holder<Node> nodeHolder(HolderNode().parse(sk::util::Container("(&())"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(5, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<HolderNode: &<HolderNode: empty>>", nodeHolder.get().inspect());
}
