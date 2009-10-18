/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Holder.cxx>
#include "PrimeNodeTest.h"
#include "../PrimeNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::pp::test::PrimeNodeTest);

sk::util::pp::test::PrimeNodeTest::
PrimeNodeTest()
{
}

sk::util::pp::test::PrimeNodeTest::
~PrimeNodeTest()
{
}

void
sk::util::pp::test::PrimeNodeTest::
setUp()
{
}

void
sk::util::pp::test::PrimeNodeTest::
tearDown()
{
}

void
sk::util::pp::test::PrimeNodeTest::
testOpenBrakets()
{
  sk::util::Container brakets;
  sk::util::Holder<Node> nodeHolder;

  PrimeNode().pushOpenBraket(brakets);
  CPPUNIT_ASSERT_EQUAL("<", brakets.toString());
}

void
sk::util::pp::test::PrimeNodeTest::
testPointer()
{
  sk::util::Holder<Node> nodeHolder(PrimeNode().parse(sk::util::Container("<null>") , 0, sk::util::Container()));
  CPPUNIT_ASSERT(nodeHolder.isEmpty() == false);
  CPPUNIT_ASSERT_EQUAL("<null>", nodeHolder.get().toString());
  CPPUNIT_ASSERT_EQUAL(0, nodeHolder.get().startPosition());
  CPPUNIT_ASSERT_EQUAL(6, nodeHolder.get().endPosition());
}
