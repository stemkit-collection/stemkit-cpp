/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Container.h>
#include <sk/util/Holder.cxx>

#include "PointerNodeTest.h"
#include "../PointerNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::PointerNodeTest);

sk::util::pp::test::PointerNodeTest::
PointerNodeTest()
{
}

sk::util::pp::test::PointerNodeTest::
~PointerNodeTest()
{
}

void
sk::util::pp::test::PointerNodeTest::
setUp()
{
}

void
sk::util::pp::test::PointerNodeTest::
tearDown()
{
}

void
sk::util::pp::test::PointerNodeTest::
testNone()
{
  CPPUNIT_ASSERT(PointerNode().parse(sk::util::Container("abc"), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(PointerNode().parse(sk::util::Container("<null"), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(PointerNode().parse(sk::util::Container("<0x1234"), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(PointerNode().parse(sk::util::Container("<0x>"), 0, sk::util::Container()) == 0);
  CPPUNIT_ASSERT(PointerNode().parse(sk::util::Container("<0x1234u>"), 0, sk::util::Container()) == 0);
}

void
sk::util::pp::test::PointerNodeTest::
testNull()
{
  sk::util::Holder<Node> nodeHolder(PointerNode().parse(sk::util::Container("   <null>") , 3, sk::util::Container()));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);

  CPPUNIT_ASSERT_EQUAL("<null>", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(3, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(9, nodeHolder.get().endPosition());
}

#include <iostream>

void
sk::util::pp::test::PointerNodeTest::
testGeneric()
{
  sk::util::Container data = "   " + sk::util::inspect(reinterpret_cast<void*>(0x12aBcc4));

  sk::util::Holder<Node> nodeHolder(PointerNode().parse(data, 3, sk::util::Container()));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);

  CPPUNIT_ASSERT_EQUAL("<0x12abcc4>", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(3, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(14, nodeHolder.get().endPosition());
}
