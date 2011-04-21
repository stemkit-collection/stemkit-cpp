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
#include <sk/util/CompoundException.h>
#include <sk/util/StandardException.h>
#include <sk/util/UnknownException.h>
#include <sk/util/IllegalStateException.h>
#include <stdexcept>

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
      if(message.startsWith("sk") == true) {
        throw sk::util::IllegalStateException("Got SK " + message);
      }
      if(message.startsWith("e") == true) {
        throw std::domain_error("Got STD " + message);
      }
      if(message.startsWith("s") == true) {
        throw "Got STR " + message;
      }
      if(message.startsWith("u") == true) {
        throw Workshop();
      }
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

void 
sk::rt::tests::ActionsTest::
test_all_executed_despite_errors_with_compound_exception()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "sk2");
  actions.add("a3", workshop, &Workshop::addMessage, "e3");
  actions.add("a4", workshop, &Workshop::addMessage, "s4");
  actions.add("a5", workshop, &Workshop::addMessage, "u5");
  actions.add("a6", workshop, &Workshop::addMessage, "m6");

  try {
    actions.perform();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <a2: Illegal state: Got SK sk2>: <a3: Got STD e3>: <a4: Got STR s4>: <a5: \?\?\?>", exception.what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m6", workshop.strings.get(1));
}

void 
sk::rt::tests::ActionsTest::
test_all_reversed_executed_despite_errors_with_compound_exception()
{
  Workshop workshop;
  sk::rt::Actions actions(true);
  CPPUNIT_ASSERT(actions.isReverse() == true);

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "sk2");
  actions.add("a3", workshop, &Workshop::addMessage, "e3");
  actions.add("a4", workshop, &Workshop::addMessage, "s4");
  actions.add("a5", workshop, &Workshop::addMessage, "u5");
  actions.add("a6", workshop, &Workshop::addMessage, "m6");

  try {
    actions.perform();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <a5: \?\?\?>: <a4: Got STR s4>: <a3: Got STD e3>: <a2: Illegal state: Got SK sk2>", exception.what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m6", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(1));
}

void 
sk::rt::tests::ActionsTest::
test_all_executed_despite_errors_no_exception_when_ignored()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "sk2");
  actions.add("a3", workshop, &Workshop::addMessage, "e3");
  actions.add("a4", workshop, &Workshop::addMessage, "s4");
  actions.add("a5", workshop, &Workshop::addMessage, "u5");
  actions.add("a6", workshop, &Workshop::addMessage, "m6");

  try {
    int number_of_errors = actions.performIgnoreErrors();
    CPPUNIT_ASSERT_EQUAL(4, number_of_errors);
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m6", workshop.strings.get(1));
}

void
sk::rt::tests::ActionsTest::
test_non_problem_actions_throw_requested_exception()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "m2");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <Illegal state: Hello>", exception.what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m2", workshop.strings.get(1));
}

void
sk::rt::tests::ActionsTest::
test_throws_requested_exception_with_action_exceptions()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "e2");
  actions.add("a3", workshop, &Workshop::addMessage, "s3");
  actions.add("a4", workshop, &Workshop::addMessage, "m4");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <Illegal state: Hello>: <a2: Got STD e2>: <a3: Got STR s3>", exception.what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m4", workshop.strings.get(1));
}

void
sk::rt::tests::ActionsTest::
test_throws_requested_exception_with_reversed_action_exceptions()
{
  Workshop workshop;
  sk::rt::Actions actions(true);
  CPPUNIT_ASSERT(actions.isReverse() == true);

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  actions.add("a2", workshop, &Workshop::addMessage, "e2");
  actions.add("a3", workshop, &Workshop::addMessage, "s3");
  actions.add("a4", workshop, &Workshop::addMessage, "m4");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <Illegal state: Hello>: <a3: Got STR s3>: <a2: Got STD e2>", exception.what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, actions.size());

  CPPUNIT_ASSERT_EQUAL(2, workshop.strings.size());
  CPPUNIT_ASSERT_EQUAL("m4", workshop.strings.get(0));
  CPPUNIT_ASSERT_EQUAL("m1", workshop.strings.get(1));
}

void
sk::rt::tests::ActionsTest::
test_exceptions_cleared_after_throw()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "e1");
  actions.add("a2", workshop, &Workshop::addMessage, "s1");

  CPPUNIT_ASSERT_THROW(actions.perform(), sk::util::CompoundException);
  CPPUNIT_ASSERT_EQUAL(0, actions.size());
  CPPUNIT_ASSERT_EQUAL(0, workshop.strings.size());

  actions.add("a1", workshop, &Workshop::addMessage, "m1");
  CPPUNIT_ASSERT_EQUAL(0, actions.performIgnoreErrors());
  CPPUNIT_ASSERT_EQUAL(1, workshop.strings.size());
}

void
sk::rt::tests::ActionsTest::
test_no_actions_after_clear()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.add("a1", workshop, &Workshop::addMessage, "e1");
  actions.add("a2", workshop, &Workshop::addMessage, "s2");

  actions.clear();
  CPPUNIT_ASSERT_EQUAL(0, actions.size());
  CPPUNIT_ASSERT_NO_THROW(actions.perform());
}

void 
sk::rt::tests::ActionsTest::
test_on_error_throws_with_undo_exceptions()
{
  Workshop workshop;
  sk::rt::Actions actions(true);

  try {
    try {
      actions.add("a1", workshop, &Workshop::addMessage, "e1");
      actions.add("a2", workshop, &Workshop::addMessage, "s2");

      throw std::domain_error("sample error");
    }
    catch(const sk::util::Exception& exception) {
      actions.performThrow(exception);
    }
    catch(const std::exception& exception) {
      actions.performThrow(sk::util::StandardException(exception));
    }
    catch(...) {
      actions.performThrow(sk::util::UnknownException());
    }
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: Compound: <sample error>: <a2: Got STR s2>: <a1: Got STD e1>", exception.what());
  }
}
