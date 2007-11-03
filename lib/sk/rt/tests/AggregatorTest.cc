/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AggregatorTest.h"
#include <sk/rt/scope/Aggregator.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::AggregatorTest);

sk::rt::tests::AggregatorTest::
AggregatorTest()
{
}

sk::rt::tests::AggregatorTest::
~AggregatorTest()
{
}

void
sk::rt::tests::AggregatorTest::
setUp()
{
}

void
sk::rt::tests::AggregatorTest::
tearDown()
{
}

void
sk::rt::tests::AggregatorTest::
testInner()
{
  scope::Aggregator aggregator;
  CPPUNIT_ASSERT_EQUAL(0, aggregator.size());

  scope::Aggregator& inner = aggregator.obtain("aaa");
  CPPUNIT_ASSERT_EQUAL(1, aggregator.size());

  CPPUNIT_ASSERT( &inner != &aggregator );
  CPPUNIT_ASSERT( &aggregator.getConfig() == &inner.getConfig() );
  CPPUNIT_ASSERT( &aggregator.getConfig() == &aggregator.obtain("aaa").getConfig() );

  CPPUNIT_ASSERT_EQUAL(1, aggregator.size());

  CPPUNIT_ASSERT( &aggregator.getConfig() == &aggregator.obtain("bbb").getConfig() );
  CPPUNIT_ASSERT_EQUAL(2, aggregator.size());

  CPPUNIT_ASSERT_EQUAL(false, aggregator.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, inner.getConfig().isLogTime());

  aggregator.getConfig().setLogTime(true);

  CPPUNIT_ASSERT_EQUAL(true, aggregator.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(true, inner.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(true, inner.obtain("bbb").obtain("ccc").getConfig().isLogTime());
}
