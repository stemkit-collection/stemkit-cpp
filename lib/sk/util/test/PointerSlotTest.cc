/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PointerSlotTest.h"
#include <sk/util/PointerSlot.h>
#include <sk/util/String.h>

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
}

void
sk::util::test::PointerSlotTest::
tearDown()
{
}

void
sk::util::test::PointerSlotTest::
testGet()
{
  String* s = new String("dcba");
  PointerSlot<String> slot(s);

  CPPUNIT_ASSERT_EQUAL(String("dcba"), slot.get());
  CPPUNIT_ASSERT_EQUAL(s, &slot.get());
}

void
sk::util::test::PointerSlotTest::
testDeprive()
{
  String* s = new String("dcba");
  PointerSlot<String> slot(s);

  String* s2 = slot.deprive();
  CPPUNIT_ASSERT_EQUAL(s, s2);

  CPPUNIT_ASSERT_THROW(slot.get(), IllegalStateException);
  CPPUNIT_ASSERT_THROW(slot.deprive(), IllegalStateException);
}

void
sk::util::test::PointerSlotTest::
testMisc()
{
  String* s = new String("abcd");
  PointerSlot<String> slot(s);

  CPPUNIT_ASSERT_EQUAL(String("*"), slot.inspect());
}
