/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "ReferenceSlotTest.h"
#include <sk/util/slot/Reference.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::ReferenceSlotTest);

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
  slot::Reference<String> slot(s);

  CPPUNIT_ASSERT_EQUAL("abcd", slot.get());
  CPPUNIT_ASSERT_EQUAL(&s, &slot.getMutable());
}

void
sk::util::test::ReferenceSlotTest::
testDeprive()
{
  String s("abcd");
  slot::Reference<String> slot(s);

  CPPUNIT_ASSERT_THROW(slot.deprive(), UnsupportedOperationException);
  CPPUNIT_ASSERT_EQUAL(String("abcd"), slot.get());
}

void
sk::util::test::ReferenceSlotTest::
testMisc()
{
  String s("abcd");
  slot::Reference<String> slot(s);

  CPPUNIT_ASSERT_EQUAL(String("&\"abcd\""), slot.inspect());
}
