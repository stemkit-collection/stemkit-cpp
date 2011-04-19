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
test_set_reverse_and_no_actions_no_problems()
{
  sk::rt::Actions actions;
  CPPUNIT_ASSERT(actions.isReverse() == false);
  actions.setReverse(true);
  CPPUNIT_ASSERT(actions.isReverse() == true);
  actions.setReverse(false);
  CPPUNIT_ASSERT(actions.isReverse() == false);

  CPPUNIT_ASSERT_NO_THROW(actions.perform());
}

namespace {
  struct Workshop {
    void addMessage(const sk::util::String& message) {
      strings << message;
    }
    sk::util::Strings strings;
  };
}

void 
sk::rt::tests::ActionsTest::
test_non_problem_actions_work_in_direct_order()
{
  Workshop workshop;
  sk::rt::Actions actions;
  CPPUNIT_ASSERT(actions.isReverse() == false);

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "m2");
  actions.add("a3", workshop, &Workshop::addMessage, "m3");

  CPPUNIT_ASSERT_EQUAL(3, actions.size());
  CPPUNIT_ASSERT_NO_THROW(actions.perform());
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(3, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m2", workshop.strings.get(1));
  CPPUNIT_ASSERT_EQUAL("m3", workshop.strings.get(2));
}

void 
sk::rt::tests::ActionsTest::
test_non_problem_actions_work_in_reverse_order()
{
  Workshop workshop;
  sk::rt::Actions actions(true);
  CPPUNIT_ASSERT(actions.isReverse() == true);

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "m2");
  actions.add("a3", workshop, &Workshop::addMessage, "m3");

  CPPUNIT_ASSERT_EQUAL(3, actions.size());
  CPPUNIT_ASSERT_NO_THROW(actions.perform());
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(3, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m3", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m2", workshop.strings.get(1));
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(2));
}

void 
sk::rt::tests::ActionsTest::
test_non_problem_actions_work_out_of_scope_without_perform()
{
  Workshop workshop;
  CPPUNIT_ASSERT_EQUAL(0, workshop.strings.size());
  {
    sk::rt::Actions actions(true);
    CPPUNIT_ASSERT(actions.isReverse() == true);

    actions.add("a1", workshop, &Workshop::addMessage, "m1");
    actions.add("a2", workshop, &Workshop::addMessage, "m2");
    actions.add("a3", workshop, &Workshop::addMessage, "m3");
  }
  CPPUNIT_ASSERT_EQUAL(3, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m3", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m2", workshop.strings.get(1));
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(2));
}
