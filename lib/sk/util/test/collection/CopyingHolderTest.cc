/*  vi: sw=2:
 *  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "CopyingHolderTest.h"
#include <sk/util/Holder.cxx>
#include <sk/util/String.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::util::test::CopyingHolderTest);

sk::util::test::CopyingHolderTest::
CopyingHolderTest()
{
}

sk::util::test::CopyingHolderTest::
~CopyingHolderTest()
{
}

void
sk::util::test::CopyingHolderTest::
setUp()
{
}

void
sk::util::test::CopyingHolderTest::
tearDown()
{
}

void
sk::util::test::CopyingHolderTest::
testClone()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Copying clone(holder.get());

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CopyingHolderTest::
testCopyConstructor()
{
  Holder<String>::Copying holder(new String("abc"));
  Holder<String>::Copying clone(holder);

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CopyingHolderTest::
testCopyFromAlias()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Aliasing alias(holder);
  Holder<String>::Copying clone(alias);

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(false, alias.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, clone.isOwner());
}

void
sk::util::test::CopyingHolderTest::
testStringLiteral()
{
  Holder<String>::Copying holder("abc");
  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(String("abc").inspect(), holder.get().inspect());
}

void
sk::util::test::CopyingHolderTest::
testAssignment()
{
  Holder<String>::Copying holder("abc");
  Holder<String>::Copying other("cba");

  CPPUNIT_ASSERT_EQUAL("cba", other.get());
  other = holder;

  CPPUNIT_ASSERT_EQUAL("abc", holder.get());
  CPPUNIT_ASSERT_EQUAL("abc", other.get());

  CPPUNIT_ASSERT_EQUAL(true, holder.isOwner());
  CPPUNIT_ASSERT_EQUAL(true, other.isOwner());
  CPPUNIT_ASSERT(&holder.get() != &other.get());
}

void
sk::util::test::CopyingHolderTest::
testAssignmentFromOther()
{
  Holder<String> holder(new String("abc"));
  Holder<String>::Aliasing alias(holder);
  Holder<String>::Copying other("cba");

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

void
sk::util::test::CopyingHolderTest::
testContains()
{
  Holder<String>::Copying holder("abc");

  CPPUNIT_ASSERT(holder.contains("abc") == true);
  CPPUNIT_ASSERT(holder.contains("zzz") == false);
}
