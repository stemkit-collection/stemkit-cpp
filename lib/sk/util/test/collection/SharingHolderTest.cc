/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "SharingHolderTest.h"
#include <sk/util/Holder.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::SharingHolderTest);

sk::util::test::SharingHolderTest::
SharingHolderTest()
{
}

sk::util::test::SharingHolderTest::
~SharingHolderTest()
{
}

void
sk::util::test::SharingHolderTest::
setUp()
{
}

void
sk::util::test::SharingHolderTest::
tearDown()
{
}

void
sk::util::test::SharingHolderTest::
testBasics()
{
  Holder<String>::Sharing holder(new String("abc"));
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, holder.getSlot().getLinks());

  {
    Holder<String>::Sharing other(holder);

    CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
    CPPUNIT_ASSERT_EQUAL(false, other.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, other.isOwner());

    CPPUNIT_ASSERT_EQUAL(2, holder.getSlot().getLinks());
    CPPUNIT_ASSERT_EQUAL(2, other.getSlot().getLinks());

    CPPUNIT_ASSERT_EQUAL(&other.get(), &holder.get());
  }

  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, holder.getSlot().getLinks());
}

void
sk::util::test::SharingHolderTest::
testAssignment()
{
  Holder<String>::Sharing holder(new String("abc"));
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, holder.getSlot().getLinks());

  Holder<String>::Sharing other;
  CPPUNIT_ASSERT_EQUAL(true, other.isEmpty());

  other = holder;

  CPPUNIT_ASSERT_EQUAL(false, other.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(2, holder.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(2, other.getSlot().getLinks());

  CPPUNIT_ASSERT_EQUAL(&other.get(), &holder.get());
}

void
sk::util::test::SharingHolderTest::
testReplacementAfterClear()
{
  Holder<String>::Sharing h1(new String("abc"));
  Holder<String>::Sharing h2(h1);

  CPPUNIT_ASSERT_EQUAL(2, h1.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(2, h2.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(&h1.get(), &h2.get());

  h1.clear();
  CPPUNIT_ASSERT_EQUAL(1, h2.getSlot().getLinks());
  h1.set(new String("cba"));

  CPPUNIT_ASSERT_EQUAL(1, h1.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(1, h2.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("cba").inspect(), h1.get().inspect());
  CPPUNIT_ASSERT_EQUAL(sk::util::String("abc").inspect(), h2.get().inspect());
}
void
sk::util::test::SharingHolderTest::
testReplacement()
{
  Holder<String>::Sharing h1(new String("abc"));
  Holder<String>::Sharing h2(h1);

  CPPUNIT_ASSERT_EQUAL(2, h1.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(2, h2.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(&h1.get(), &h2.get());

  h1.set(new String("cba"));

  CPPUNIT_ASSERT_EQUAL(2, h1.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(2, h2.getSlot().getLinks());
  CPPUNIT_ASSERT_EQUAL(&h1.get(), &h2.get());
}
