/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "UserTest.h"
#include <sk/util/Holder.cxx>
#include <sk/sys/User.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::sys::test::UserTest);

sk::sys::test::UserTest::
UserTest()
{
}

sk::sys::test::UserTest::
~UserTest()
{
}

void
sk::sys::test::UserTest::
setUp()
{
}

void
sk::sys::test::UserTest::
tearDown()
{
}

void
sk::sys::test::UserTest::
testFind()
{
  sk::util::Holder<sk::sys::User> holder;

  CPPUNIT_ASSERT_EQUAL(true, sk::sys::User::find("root", holder));
  CPPUNIT_ASSERT_EQUAL(sk::util::String("root"), holder.get().getName());
  CPPUNIT_ASSERT_EQUAL(0U, holder.get().getUid());
}

void
sk::sys::test::UserTest::
testAuthenticate()
{
  sk::util::Holder<sk::sys::User> holder;

  CPPUNIT_ASSERT_EQUAL(true, sk::sys::User::find("root", holder));
  CPPUNIT_ASSERT_EQUAL(false, holder.get().authenticate("root"));
}
