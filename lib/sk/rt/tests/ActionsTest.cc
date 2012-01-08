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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "m2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "m3");

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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "m2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "m3");

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

    actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
    actions.addMethod("a2", workshop, &Workshop::addMessage, "m2");
    actions.addMethod("a3", workshop, &Workshop::addMessage, "m3");
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "sk2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "e3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "s4");
  actions.addMethod("a5", workshop, &Workshop::addMessage, "u5");
  actions.addMethod("a6", workshop, &Workshop::addMessage, "m6");

  try {
    actions.perform();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 4: a2: Illegal state: Got SK sk2", exception.what());
    CPPUNIT_ASSERT_EQUAL(4, exception.size());

    CPPUNIT_ASSERT_EQUAL("a2: Illegal state: Got SK sk2", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a3: Got STD e3", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a4: Got STR s4", exception.exceptionAt(2).what());
    CPPUNIT_ASSERT_EQUAL("a5: \?\?\?", exception.exceptionAt(3).what());
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "sk2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "e3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "s4");
  actions.addMethod("a5", workshop, &Workshop::addMessage, "u5");
  actions.addMethod("a6", workshop, &Workshop::addMessage, "m6");

  try {
    actions.perform();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 4: a5: \?\?\?", exception.what());
    CPPUNIT_ASSERT_EQUAL(4, exception.size());

    CPPUNIT_ASSERT_EQUAL("a5: \?\?\?", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a4: Got STR s4", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a3: Got STD e3", exception.exceptionAt(2).what());
    CPPUNIT_ASSERT_EQUAL("a2: Illegal state: Got SK sk2", exception.exceptionAt(3).what());
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "sk2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "e3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "s4");
  actions.addMethod("a5", workshop, &Workshop::addMessage, "u5");
  actions.addMethod("a6", workshop, &Workshop::addMessage, "m6");

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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "m2");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 1: Illegal state: Hello", exception.what());
    CPPUNIT_ASSERT_EQUAL(1, exception.size());

    CPPUNIT_ASSERT_EQUAL("Illegal state: Hello", exception.exceptionAt(0).what());
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "e2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "s3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "m4");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 3: Illegal state: Hello", exception.what());
    CPPUNIT_ASSERT_EQUAL(3, exception.size());

    CPPUNIT_ASSERT_EQUAL("Illegal state: Hello", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a2: Got STD e2", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a3: Got STR s3", exception.exceptionAt(2).what());
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "e2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "s3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "m4");

  try {
    actions.performThrow(sk::util::IllegalStateException("Hello"));
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 3: Illegal state: Hello", exception.what());
    CPPUNIT_ASSERT_EQUAL(3, exception.size());

    CPPUNIT_ASSERT_EQUAL("Illegal state: Hello", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a3: Got STR s3", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a2: Got STD e2", exception.exceptionAt(2).what());
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

  actions.addMethod("a1", workshop, &Workshop::addMessage, "e1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "s1");

  CPPUNIT_ASSERT_THROW(actions.perform(), sk::util::CompoundException);
  CPPUNIT_ASSERT_EQUAL(0, actions.size());
  CPPUNIT_ASSERT_EQUAL(0, workshop.strings.size());

  actions.addMethod("a1", workshop, &Workshop::addMessage, "m1");
  CPPUNIT_ASSERT_EQUAL(0, actions.performIgnoreErrors());
  CPPUNIT_ASSERT_EQUAL(1, workshop.strings.size());
}

void
sk::rt::tests::ActionsTest::
test_no_actions_after_clear()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.addMethod("a1", workshop, &Workshop::addMessage, "e1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "s2");

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
      actions.addMethod("a1", workshop, &Workshop::addMessage, "e1");
      actions.addMethod("a2", workshop, &Workshop::addMessage, "s2");

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
    CPPUNIT_ASSERT_EQUAL("Compound: 3: sample error", exception.what());
    CPPUNIT_ASSERT_EQUAL(3, exception.size());

    CPPUNIT_ASSERT_EQUAL("sample error", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a2: Got STR s2", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a1: Got STD e1", exception.exceptionAt(2).what());
  }
}

void
sk::rt::tests::ActionsTest::
test_performing_until_success_succeeds_when_one_successful()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.addMethod("a1", workshop, &Workshop::addMessage, "e1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "e2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "m3");
  actions.addMethod("a4", workshop, &Workshop::addMessage, "m4");
  actions.addMethod("a5", workshop, &Workshop::addMessage, "e5");

  CPPUNIT_ASSERT_EQUAL(2, actions.performUntilSuccess());
  CPPUNIT_ASSERT_EQUAL(1, workshop.strings.size());
}

void
sk::rt::tests::ActionsTest::
test_performing_until_success_fails_on_all_errors()
{
  Workshop workshop;
  sk::rt::Actions actions;

  actions.addMethod("a1", workshop, &Workshop::addMessage, "e1");
  actions.addMethod("a2", workshop, &Workshop::addMessage, "e2");
  actions.addMethod("a3", workshop, &Workshop::addMessage, "e3");

  try {
    actions.performUntilSuccess(true);
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::CompoundException& exception) {
    CPPUNIT_ASSERT_EQUAL("Compound: 3: a3: Got STD e3", exception.what());
    CPPUNIT_ASSERT_EQUAL(3, exception.size());

    CPPUNIT_ASSERT_EQUAL("a3: Got STD e3", exception.exceptionAt(0).what());
    CPPUNIT_ASSERT_EQUAL("a2: Got STD e2", exception.exceptionAt(1).what());
    CPPUNIT_ASSERT_EQUAL("a1: Got STD e1", exception.exceptionAt(2).what());
  }
  catch(const std::exception& exception) {
    CPPUNIT_FAIL(sk::util::String("Unexpected exception: ") + exception.what());
  }
  catch(...) {
    CPPUNIT_FAIL("Unexpected unknown exception");
  }
  CPPUNIT_ASSERT_EQUAL(0, workshop.strings.size());
}

namespace {
  sk::util::Strings __testStrings;
}

static void f1() {
  __testStrings.add("f1");
}

extern "C" void f2() {
  __testStrings.add("f2");
}

void
sk::rt::tests::ActionsTest::
test_can_add_global_no_param_function()
{
  __testStrings.clear();
  {
    sk::rt::Actions actions;
    actions.addFunctor("F1", f1);
    actions.addFunctor("F2", f2);

    CPPUNIT_ASSERT_EQUAL(0, __testStrings.size());
  }
  CPPUNIT_ASSERT_EQUAL(2, __testStrings.size());
  CPPUNIT_ASSERT_EQUAL("f1", __testStrings.get(0));
  CPPUNIT_ASSERT_EQUAL("f2", __testStrings.get(1));
}

static void fp1(const std::string s) {
  __testStrings.add(sk::util::String("fp1:std::string:") + s);
}

static void fp2(const int n) {
  __testStrings.add(sk::util::String("fp1:int:") + sk::util::String::valueOf(n));
}

static void fp3(const char* s) {
  __testStrings.add(sk::util::String("fp1:const-chars:") + s);
}

static int fp4(char* s) {
  __testStrings.add(sk::util::String("fp1:chars:") + s);
  return 0;
}

void
sk::rt::tests::ActionsTest::
test_can_add_global_one_param_function()
{
  char chars[] = "mmm";

  __testStrings.clear();
  {
    sk::rt::Actions actions;
    actions.addFunctor("FP1", fp1, std::string("abc"));
    actions.addFunctor("FP2", fp2, 78);
    actions.addFunctor("FP3", fp3, "uuu");
    actions.addFunctor("FP4", fp4, chars);

    CPPUNIT_ASSERT_EQUAL(0, __testStrings.size());
  }
  CPPUNIT_ASSERT_EQUAL(4, __testStrings.size());
  CPPUNIT_ASSERT_EQUAL("fp1:std::string:abc", __testStrings.get(0));
  CPPUNIT_ASSERT_EQUAL("fp1:int:78", __testStrings.get(1));
  CPPUNIT_ASSERT_EQUAL("fp1:const-chars:uuu", __testStrings.get(2));
  CPPUNIT_ASSERT_EQUAL("fp1:chars:mmm", __testStrings.get(3));
}

static void fppp1(const sk::util::String& s, const int n, int& r)
{
  __testStrings.add(sk::util::String("fppp1:std::string:") + s);
  r += (s.size() + n);
}

extern "C" void fppp2(const sk::util::String& s, const int n, int r)
{
  __testStrings.add(sk::util::String("fppp2:std::string:") + s + ":" + sk::util::String::valueOf(s.size() + n + r));
}

void
sk::rt::tests::ActionsTest::
test_can_add_global_multi_param_function()
{
  __testStrings.clear();
  int r = 2;
  int n = 9;
  {
    sk::rt::Actions actions;
    sk::util::String s("hehehe");
    actions.addFunctor("FPPP1", fppp1, s, 4, r);
    actions.addFunctor("FPPP2", fppp2, "ccc", 4, 7);
    actions.addFunctor("FPPP3", fppp2, "ccc", 4, n);

    CPPUNIT_ASSERT_EQUAL(0, __testStrings.size());
  }
  CPPUNIT_ASSERT_EQUAL(3, __testStrings.size());
  CPPUNIT_ASSERT_EQUAL("fppp1:std::string:hehehe", __testStrings.get(0));
  CPPUNIT_ASSERT_EQUAL(12, r);

  CPPUNIT_ASSERT_EQUAL("fppp2:std::string:ccc:14", __testStrings.get(1));
  CPPUNIT_ASSERT_EQUAL("fppp2:std::string:ccc:16", __testStrings.get(2));
  CPPUNIT_ASSERT_EQUAL(9, n);
}
