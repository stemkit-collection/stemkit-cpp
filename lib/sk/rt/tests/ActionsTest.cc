/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ActionsTest.h"
#include <sk/rt/Actions.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::tests::ActionsTest);

sk::rt::tests::ActionsTest::
ActionsTest()
{
}

sk::rt::tests::ActionsTest::
~ActionsTest()
{
}

void
sk::rt::tests::ActionsTest::
setUp()
{
}

void
sk::rt::tests::ActionsTest::
tearDown()
{
}

void
sk::rt::tests::ActionsTest::
test_no_actions_no_problems()
{
  Actions actions;
  CPPUNIT_ASSERT_NO_THROW(actions.perform());
}
