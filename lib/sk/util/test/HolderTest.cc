/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "HolderTest.h"
#include <sk/util/Holder.h>
#include "Probe.h"

sk::util::test::HolderTest::
HolderTest()
{
}

sk::util::test::HolderTest::
~HolderTest()
{
}

void
sk::util::test::HolderTest::
setUp()
{
  Probe::resetCounter();
}

void
sk::util::test::HolderTest::
tearDown()
{
  Probe::resetCounter();
}

void
sk::util::test::HolderTest::
testCreateWithReference()
{
  Probe probe("abc");
  Holder<Probe> holder(probe);

  CPPUNIT_ASSERT_EQUAL(&probe, &holder.get());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.contains(probe));
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));
}

void
sk::util::test::HolderTest::
testCreateWithPointer()
{
  Probe* probe = new Probe("abc");
  Holder<Probe> holder(probe);

  CPPUNIT_ASSERT_EQUAL(probe, &holder.get());
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.contains(*probe));
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));
}

void
sk::util::test::HolderTest::
testCreateEmpty()
{
  Holder<Probe> holder;

  CPPUNIT_ASSERT_EQUAL(true, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(false, holder.contains(Probe("bbb")));

  CPPUNIT_ASSERT_THROW(holder.get(), IllegalStateException);
}
