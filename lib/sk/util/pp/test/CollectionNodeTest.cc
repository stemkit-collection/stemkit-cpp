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

#include "CollectionNodeTest.h"
#include "../CollectionNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::CollectionNodeTest);

sk::util::pp::test::CollectionNodeTest::
CollectionNodeTest()
{
}

sk::util::pp::test::CollectionNodeTest::
~CollectionNodeTest()
{
}

void
sk::util::pp::test::CollectionNodeTest::
setUp()
{
}

void
sk::util::pp::test::CollectionNodeTest::
tearDown()
{
}

void
sk::util::pp::test::CollectionNodeTest::
testEmpty()
{
  sk::util::Holder<Node> nodeHolder(CollectionNode().parse(sk::util::Container("[ ]"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(3, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<CollectionNode: empty>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::CollectionNodeTest::
testOne()
{
  sk::util::Holder<Node> nodeHolder(CollectionNode().parse(sk::util::Container("[1: 0*\"abcd\" ]"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(14, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<CollectionNode:1: 0*<TextNode: \"\\\"abcd\\\"\">>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::CollectionNodeTest::
testMany()
{
  sk::util::Holder<Node> nodeHolder(CollectionNode().parse(sk::util::Container("  [2: 0*(), 1&() ]"), 2, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(2, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(18, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<CollectionNode:2: 0*<HolderNode: empty>, 1&<HolderNode: empty>>", nodeHolder.get().inspect());
}
