/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "CloningHolderTest.h"
#include <sk/util/Holder.cxx>
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::CloningHolderTest);

sk::util::test::CloningHolderTest::
CloningHolderTest()
{
}

sk::util::test::CloningHolderTest::
~CloningHolderTest()
{
}

void
sk::util::test::CloningHolderTest::
setUp()
{
}

void
sk::util::test::CloningHolderTest::
tearDown()
{
}

void
sk::util::test::CloningHolderTest::
testClone()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Cloning clone(holder.get());

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CloningHolderTest::
testCopyConstructor()
{
  Holder<String>::Cloning holder(new String("abc"));
  Holder<String>::Cloning clone(holder);

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CloningHolderTest::
testCopyFromAlias()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Aliasing alias(holder);
  Holder<String>::Cloning clone(alias);

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(false, alias.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CloningHolderTest::
testStringLiteral()
{
  Holder<String>::Cloning holder("abc");
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), holder.get().inspect());
}

void
sk::util::test::CloningHolderTest::
testAssignment()
{
  Holder<String>::Cloning holder("abc");
  Holder<String>::Cloning other("cba");

  CPPUNIT_ASSERT_EQUAL(String("cba").inspect(), other.get().inspect());
  other = holder;

  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), holder.get().inspect());
  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), other.get().inspect());

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT(&holder.get() != &other.get());
}

void
sk::util::test::CloningHolderTest::
testAssignmentFromOther()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Aliasing alias(holder);
  Holder<String>::Cloning other("cba");

  CPPUNIT_ASSERT_EQUAL(String("cba").inspect(), other.get().inspect());
  other = alias;

  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), holder.get().inspect());
  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), other.get().inspect());

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(false, alias.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT(&holder.get() != &other.get());
  CPPUNIT_ASSERT(&alias.get() != &other.get());
}
