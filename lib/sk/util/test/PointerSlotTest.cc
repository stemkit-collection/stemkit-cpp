/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PointerSlotTest.h"
#include <sk/util/PointerSlot.hxx>
#include <sk/util/PointerSlot.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NullPointerException.h>
#include <sk/util/String.h>
#include "Probe.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::PointerSlotTest);

sk::util::test::PointerSlotTest::
PointerSlotTest()
{
}

sk::util::test::PointerSlotTest::
~PointerSlotTest()
{
}

void
sk::util::test::PointerSlotTest::
setUp()
{
  Probe::resetCounter();
}

void
sk::util::test::PointerSlotTest::
tearDown()
{
  Probe::resetCounter();
}

void
sk::util::test::PointerSlotTest::
testGet()
{
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
  {
    Probe* probe = new Probe("dcba");
    PointerSlot<Probe> slot(probe);

    CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
    CPPUNIT_ASSERT_EQUAL(String("dcba"), slot.get().getName());
    CPPUNIT_ASSERT_EQUAL(probe, &slot.get());
  }
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
}

void
sk::util::test::PointerSlotTest::
testDeprive()
{
  Probe* probe = new Probe("dcba");
  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
  {
    PointerSlot<Probe> slot(probe);

    CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
    Probe* probe2 = slot.deprive();

    CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());
    CPPUNIT_ASSERT_EQUAL(probe, probe2);

    CPPUNIT_ASSERT_THROW(slot.get(), MissingResourceException);
    CPPUNIT_ASSERT_THROW(slot.deprive(), MissingResourceException);
  }
  CPPUNIT_ASSERT_EQUAL(1, Probe::getCounter());

  delete probe;
  CPPUNIT_ASSERT_EQUAL(0, Probe::getCounter());
}

void
sk::util::test::PointerSlotTest::
testMisc()
{
  String* s = new String("abcd");
  PointerSlot<String> slot(s);

  CPPUNIT_ASSERT_THROW(new PointerSlot<String>(0), NullPointerException);
  CPPUNIT_ASSERT_EQUAL(String("*"), slot.inspect());
}
