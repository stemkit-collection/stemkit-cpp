/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ReferenceSlotTest.h"
#include <sk/util/ReferenceSlot.h>
#include <sk/util/String.h>

sk::util::test::ReferenceSlotTest::
ReferenceSlotTest()
{
}

sk::util::test::ReferenceSlotTest::
~ReferenceSlotTest()
{
}

void
sk::util::test::ReferenceSlotTest::
setUp()
{
}

void
sk::util::test::ReferenceSlotTest::
tearDown()
{
}

void
sk::util::test::ReferenceSlotTest::
testGet()
{
  String s("abcd");
  ReferenceSlot<String> slot(s);

  CPPUNIT_ASSERT_EQUAL(String("abcd"), slot.get());
  CPPUNIT_ASSERT_EQUAL(&s, &slot.get());
}

void
sk::util::test::ReferenceSlotTest::
testDeprive()
{
  String s("abcd");
  ReferenceSlot<String> slot(s);

  CPPUNIT_ASSERT_THROW(slot.deprive(), IllegalStateException);
  CPPUNIT_ASSERT_EQUAL(String("abcd"), slot.get());
}

void
sk::util::test::ReferenceSlotTest::
testMisc()
{
  String s("abcd");
  ReferenceSlot<String> slot(s);

  CPPUNIT_ASSERT_EQUAL(String("&"), slot.inspect());
}
