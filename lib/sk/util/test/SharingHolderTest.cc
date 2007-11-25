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
  CPPUNIT_ASSERT_EQUAL(1, holder.getLinks());

  {
    Holder<String>::Sharing other(holder);

    CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
    CPPUNIT_ASSERT_EQUAL(false, other.isEmpty());
    CPPUNIT_ASSERT_EQUAL(true, other.isOwner());

    CPPUNIT_ASSERT_EQUAL(2, holder.getLinks());
    CPPUNIT_ASSERT_EQUAL(2, other.getLinks());

    CPPUNIT_ASSERT_EQUAL(&other.get(), &holder.get());
  }

  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, holder.getLinks());
}

void
sk::util::test::SharingHolderTest::
testAssignment()
{
  Holder<String>::Sharing holder(new String("abc"));
  CPPUNIT_ASSERT_EQUAL(false, holder.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(1, holder.getLinks());

  Holder<String>::Sharing other;
  CPPUNIT_ASSERT_EQUAL(true, other.isEmpty());

  other = holder;

  CPPUNIT_ASSERT_EQUAL(false, other.isEmpty());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(2, holder.getLinks());
  CPPUNIT_ASSERT_EQUAL(2, other.getLinks());

  CPPUNIT_ASSERT_EQUAL(&other.get(), &holder.get());
}
