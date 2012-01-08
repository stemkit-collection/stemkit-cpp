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

#include "StructNodeTest.h"
#include "../StructNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::StructNodeTest);

sk::util::pp::test::StructNodeTest::
StructNodeTest()
{
}

sk::util::pp::test::StructNodeTest::
~StructNodeTest()
{
}

void
sk::util::pp::test::StructNodeTest::
setUp()
{
}

void
sk::util::pp::test::StructNodeTest::
tearDown()
{
}

void
sk::util::pp::test::StructNodeTest::
testEmpty()
{
  sk::util::Holder<Node> nodeHolder(StructNode().parse(sk::util::Container("<Object: >"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(10, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<StructNode:Object: empty>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::StructNodeTest::
testOne()
{
  sk::util::Holder<Node> nodeHolder(StructNode().parse(sk::util::Container("<Abc: n1=()>"), 0, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(12, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<StructNode:Abc: n1=<HolderNode: empty>>", nodeHolder.get().inspect());
}

void
sk::util::pp::test::StructNodeTest::
testMany()
{
  sk::util::Holder<Node> nodeHolder(StructNode().parse(sk::util::Container("   <Abc: n1=(), n2=zzz>"), 3, sk::util::Container("")));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL(3, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(23, nodeHolder.get().endPosition());
  CPPUNIT_ASSERT_EQUAL("<StructNode:Abc: n1=<HolderNode: empty>, n2=<TextNode: \"zzz\">>", nodeHolder.get().inspect());
}
