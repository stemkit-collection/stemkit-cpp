/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PointerSlotTest.h"
#include <sk/util/slot/Pointer.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/util/NullPointerException.h>
#include <sk/util/String.h>
#include <sk/util/test/Probe.cxx>

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
  test::Probe<String>::resetCounter();
}

void
sk::util::test::PointerSlotTest::
tearDown()
{
  test::Probe<String>::resetCounter();
}

void
sk::util::test::PointerSlotTest::
testGet()
{
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
  {
    test::Probe<String>* probe = new test::Probe<String>("dcba");
    slot::Pointer<test::Probe<String> > slot(probe);

    CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
    CPPUNIT_ASSERT_EQUAL("dcba", slot.get());
    CPPUNIT_ASSERT_EQUAL(probe, &slot.get());
  }
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
}

void
sk::util::test::PointerSlotTest::
testDeprive()
{
  test::Probe<String>* probe = new test::Probe<String>("dcba");
  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
  {
    slot::Pointer<test::Probe<String> > slot(probe);

    CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
    test::Probe<String>* probe2 = slot.deprive();

    CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());
    CPPUNIT_ASSERT_EQUAL(probe, probe2);

    CPPUNIT_ASSERT_THROW(slot.get(), MissingResourceException);
    CPPUNIT_ASSERT_THROW(slot.deprive(), MissingResourceException);
  }
  CPPUNIT_ASSERT_EQUAL(1, test::Probe<String>::getCounter());

  delete probe;
  CPPUNIT_ASSERT_EQUAL(0, test::Probe<String>::getCounter());
}

void
sk::util::test::PointerSlotTest::
testMisc()
{
  String* s = new String("abcd");
  slot::Pointer<String> slot(s);

  CPPUNIT_ASSERT_THROW(new slot::Pointer<String>(0), NullPointerException);
  CPPUNIT_ASSERT_EQUAL("*\"abcd\"", slot.inspect());

  delete slot.deprive();
  CPPUNIT_ASSERT_EQUAL("*<null>", slot.inspect());
}
