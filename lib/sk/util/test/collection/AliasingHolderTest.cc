/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "AliasingHolderTest.h"
#include <sk/util/Holder.cxx>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::AliasingHolderTest);

sk::util::test::AliasingHolderTest::
AliasingHolderTest()
{
}

sk::util::test::AliasingHolderTest::
~AliasingHolderTest()
{
}

void
sk::util::test::AliasingHolderTest::
setUp()
{
}

void
sk::util::test::AliasingHolderTest::
tearDown()
{
}

void
sk::util::test::AliasingHolderTest::
testBasics()
{
  Holder<String>::Aliasing holder(new String("abc"));
  Holder<String>::Aliasing other(holder);

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(false, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(&holder.get(), &other.get());
}

void
sk::util::test::AliasingHolderTest::
testAssignment()
{
  Holder<String>::Aliasing holder(new String("aaa"));
  Holder<String>::Aliasing other(new String("zzz"));

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(String("zzz").inspect(), other.get().inspect());

  other = holder;

  CPPUNIT_ASSERT_EQUAL(false, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(&holder.get(), &other.get());
}

void
sk::util::test::AliasingHolderTest::
testAssignmentFromOther()
{
  Holder<String>::Copying holder("aaa");
  Holder<String>::Aliasing other(new String("zzz"));

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT_EQUAL("zzz", other.get());

  other = holder;

  CPPUNIT_ASSERT_EQUAL(false, other.isOwner());
  CPPUNIT_ASSERT_EQUAL(&holder.get(), &other.get());
}

void
sk::util::test::AliasingHolderTest::
testAssignmentFromMutable()
{
  const String s1("aaa");

  Holder<String> h1(s1);
  CPPUNIT_ASSERT(h1.isMutable() == false);

  Holder<String> h2(new String("bbb"));
  CPPUNIT_ASSERT(h2.isMutable() == true);

  Holder<String>::Aliasing other;
  CPPUNIT_ASSERT(other.isEmpty() == true);

  other = h1;

  CPPUNIT_ASSERT(other.isOwner() == false);
  CPPUNIT_ASSERT(other.isMutable() == false);
  CPPUNIT_ASSERT_EQUAL(&h1.get(), &other.get());

  other = h2;

  CPPUNIT_ASSERT(other.isOwner() == false);
  CPPUNIT_ASSERT(other.isMutable() == true);
  CPPUNIT_ASSERT_EQUAL(&h2.get(), &other.get());
}
