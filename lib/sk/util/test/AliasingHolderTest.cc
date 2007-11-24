/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
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
