/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AgregatorTest.h"
#include <sk/rt/scope/Agregator.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::AgregatorTest);

sk::rt::tests::AgregatorTest::
AgregatorTest()
{
}

sk::rt::tests::AgregatorTest::
~AgregatorTest()
{
}

void
sk::rt::tests::AgregatorTest::
setUp()
{
}

void
sk::rt::tests::AgregatorTest::
tearDown()
{
}

void
sk::rt::tests::AgregatorTest::
testInner()
{
  scope::Agregator agregator;
  CPPUNIT_ASSERT_EQUAL(0, agregator.size());

  scope::Agregator& inner = agregator.obtain("aaa");
  CPPUNIT_ASSERT_EQUAL(1, agregator.size());

  CPPUNIT_ASSERT( &inner != &agregator );
  CPPUNIT_ASSERT( &agregator.getConfig() == &inner.getConfig() );
  CPPUNIT_ASSERT( &agregator.getConfig() == &agregator.obtain("aaa").getConfig() );

  CPPUNIT_ASSERT_EQUAL(1, agregator.size());

  CPPUNIT_ASSERT( &agregator.getConfig() == &agregator.obtain("bbb").getConfig() );
  CPPUNIT_ASSERT_EQUAL(2, agregator.size());

  CPPUNIT_ASSERT_EQUAL(false, agregator.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(false, inner.getConfig().isLogTime());

  agregator.getConfig().setLogTime(true);

  CPPUNIT_ASSERT_EQUAL(true, agregator.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(true, inner.getConfig().isLogTime());
  CPPUNIT_ASSERT_EQUAL(true, inner.obtain("bbb").obtain("ccc").getConfig().isLogTime());
}
