/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "ConditionMediatorTest.h"

#include <sk/util/Holder.cxx>
#include <sk/util/Strings.h>
#include <sk/rt/Mutex.h>
#include <sk/rt/TimeoutException.h>
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/Locker.h>
#include <sk/rt/Thread.h>

#include <time.h>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ConditionMediatorTest);

sk::rt::thread::tests::ConditionMediatorTest::
ConditionMediatorTest()
{
}

sk::rt::thread::tests::ConditionMediatorTest::
~ConditionMediatorTest()
{
}

sk::rt::Lock&
sk::rt::thread::tests::ConditionMediatorTest::
mutex()
{
  return _mutexHolder.getMutable();
}

void
sk::rt::thread::tests::ConditionMediatorTest::
setUp()
{
  _mutexHolder.set(new sk::rt::Mutex);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
tearDown()
{
  _mutexHolder.clear();
}

void
sk::rt::thread::tests::ConditionMediatorTest::
ensureLocked(sk::rt::thread::Condition& condition, bool& indicator)
{
  CPPUNIT_ASSERT_MESSAGE("Initial indicator value must be false", indicator == false);
  CPPUNIT_ASSERT(mutex().isLocked() == true);

  indicator = true;
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_default_blocking_but_can_be_changed()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  CPPUNIT_ASSERT(mediator.isBlocking() == true);
  mediator.setBlocking(false);
  CPPUNIT_ASSERT(mediator.isBlocking() == false);
  mediator.setBlocking(true);
  CPPUNIT_ASSERT(mediator.isBlocking() == true);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_blocking_locks_invokes_and_unlocks()
{
  CPPUNIT_ASSERT(mutex().isLocked() == false);
  sk::rt::thread::ConditionMediator mediator(mutex());
  CPPUNIT_ASSERT(mutex().isLocked() == false);

  bool method_invoked_indicator = false;
  CPPUNIT_ASSERT(mediator.syncMethod(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == true);
  CPPUNIT_ASSERT(method_invoked_indicator == true);

  CPPUNIT_ASSERT(mutex().isLocked() == false);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_non_blocking_locks_when_available_and_fails_otherwise()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  bool method_invoked_indicator = false;
  CPPUNIT_ASSERT(mediator.syncMethod(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == true);
  CPPUNIT_ASSERT(method_invoked_indicator == true);

  mediator.setBlocking(false);
  sk::rt::Locker locker(mutex());
  method_invoked_indicator = false;

  CPPUNIT_ASSERT(mediator.syncMethod(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == false);
  CPPUNIT_ASSERT(method_invoked_indicator == false);
}

namespace {
  struct UnlockWaitingInvocator : public virtual sk::rt::Runnable {
    UnlockWaitingInvocator(sk::rt::thread::ConditionMediator& m)
      : mediator(m), moment(0), status(false) {}

    void registerTime(sk::rt::thread::Condition& condition) {
      moment = time(0);
    }

    void run() {
      status = mediator.syncMethod(*this, &UnlockWaitingInvocator::registerTime);
    }
    volatile bool status;
    volatile time_t moment;
    sk::rt::thread::ConditionMediator& mediator;
  };
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_blocking_waits_until_unlocked_then_invokes()
{
  sk::rt::thread::ConditionMediator mediator(mutex());

  UnlockWaitingInvocator sampler(mediator);
  sk::rt::Thread thread(sampler);
  sk::rt::Locker locker(mutex());

  time_t now = time(0);
  thread.start();
  sk::rt::Thread::sleep(2000);

  CPPUNIT_ASSERT(thread.isAlive() == true);

  locker.unlock();
  thread.join();

  CPPUNIT_ASSERT(thread.isAlive() == false);
  CPPUNIT_ASSERT(sampler.status == true);
  CPPUNIT_ASSERT(sampler.moment != 0);
  CPPUNIT_ASSERT((sampler.moment - now) >= 2);

  CPPUNIT_ASSERT(mutex().isLocked() == false);
}

namespace {
  struct ConditionWaiter : public virtual sk::rt::Runnable {
    ConditionWaiter(sk::rt::thread::ConditionMediator& cm, int ch, int ms)
      : mediator(cm), channel(ch), milliseconds(ms), event(false), timeout(false), status(false), triggered(false) {}

    void waitCondition(sk::rt::thread::Condition& condition, int milliseconds) {
      while(event == false) {
        (milliseconds == 0 ? condition.on(channel).wait() : condition.on(channel).wait(milliseconds));
      }
      triggered = true;
    }

    void run() {
      try {
        status = mediator.syncMethod(*this, &ConditionWaiter::waitCondition, milliseconds);
      }
      catch(const sk::rt::TimeoutException& exception) {
        timeout = true;
      }
    }

    sk::rt::thread::ConditionMediator& mediator;
    const int channel;
    const int milliseconds;
    volatile bool event;
    volatile bool timeout;
    volatile bool status;
    volatile bool triggered;
  };
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_condition_wait_times_out()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  ConditionWaiter waiter(mediator, 0, 2000);
  sk::rt::Thread thread(waiter);
  thread.start();

  sk::rt::Thread::sleep(1000);
  CPPUNIT_ASSERT(thread.isAlive() == true);

  sk::rt::Thread::sleep(2000);
  CPPUNIT_ASSERT(thread.isAlive() == false);

  CPPUNIT_ASSERT(waiter.timeout == true);
  CPPUNIT_ASSERT(waiter.status == false);
  CPPUNIT_ASSERT(waiter.triggered == false);
}

namespace {
  void announceCondition(sk::rt::thread::Condition& condition, int channel) {
    condition.on(channel).announce();
  }
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_condition_wait_succeeds_on_announce()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  ConditionWaiter waiter(mediator, 0, 2000);
  sk::rt::Thread thread(waiter);
  thread.start();

  sk::rt::Thread::sleep(1000);
  CPPUNIT_ASSERT(thread.isAlive() == true);

  CPPUNIT_ASSERT(mutex().isLocked() == false);
  waiter.event = true;
  mediator.syncFunctor(announceCondition, 0);
  sk::rt::Thread::sleep(1000);

  CPPUNIT_ASSERT(mutex().isLocked() == false);
  CPPUNIT_ASSERT(thread.isAlive() == false);

  CPPUNIT_ASSERT(waiter.timeout == false);
  CPPUNIT_ASSERT(waiter.status == true);
  CPPUNIT_ASSERT(waiter.triggered == true);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_multi_channel_conditions()
{
  enum {
    EVENT_1,
    EVENT_2,
    NUMBER_OF_EVENTS
  };
  sk::rt::thread::ConditionMediator mediator(mutex(), NUMBER_OF_EVENTS);
  ConditionWaiter w1(mediator, EVENT_1, 5000);
  ConditionWaiter w2(mediator, EVENT_2, 5000);

  sk::rt::Thread t1(w1);
  sk::rt::Thread t2(w2);

  t1.start();
  t2.start();

  sk::rt::Thread::sleep(1000);
  CPPUNIT_ASSERT(t1.isAlive() == true);
  CPPUNIT_ASSERT(t2.isAlive() == true);
  CPPUNIT_ASSERT(mutex().isLocked() == false);

  w1.event = true;
  mediator.syncFunctor(announceCondition, int(EVENT_1));
  sk::rt::Thread::sleep(1000);

  CPPUNIT_ASSERT(t1.isAlive() == false);
  CPPUNIT_ASSERT(t2.isAlive() == true);

  CPPUNIT_ASSERT(w1.triggered == true);
  CPPUNIT_ASSERT(w2.triggered == false);

  w2.event = true;
  mediator.syncFunctor(announceCondition, int(EVENT_2));
  sk::rt::Thread::sleep(1000);

  CPPUNIT_ASSERT(t2.isAlive() == false);
  CPPUNIT_ASSERT(w2.triggered == true);
}

namespace {
  sk::util::Strings __strings;

  void dummy(sk::rt::thread::Condition& condition) {
    __strings << "dummy";
  }

  void preserve(sk::rt::thread::Condition& condition, const sk::util::String& s) {
    __strings << "preserve:" + s;
  }

  void make_zero(sk::rt::thread::Condition& condition, int& value) {
    __strings << "make_zero:" + sk::util::String::valueOf(value);
    value = 0;
  }

  void concat_strings(sk::rt::thread::Condition& condition, const sk::util::String& s1, const sk::util::String& s2) {
    __strings << "concat_strings:" + s1 + s2;
  }

  void make_length(sk::rt::thread::Condition& condition, const sk::util::String& s, int& length) {
    __strings << "make_length:" + s + ":" + sk::util::String::valueOf(length);
    length = s.length();
  }

  void concat_many_strings(sk::rt::thread::Condition& condition, const sk::util::String& s1, const sk::util::String& s2, const std::string& s3) {
    __strings << "concat_strings:" + s1 + s2 + s3;
  }

  void concat_and_make_length(sk::rt::thread::Condition& condition, const sk::util::String& s1, const std::string& s2, int& length) {
    __strings << "concat_and_make_length:" + s1 + s2 + ":" + sk::util::String::valueOf(length);
    length = s1.length() + s2.length();
  }
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_invoking_multi_param_functors()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  int value = 127;
  int size1 = 3;
  int size2 = 5;

  __strings.clear();

  mediator.syncFunctor(dummy);
  mediator.syncFunctor(preserve, "abc");
  mediator.syncFunctor(make_zero, value);
  mediator.syncFunctor(concat_strings, "aaa", "bbb");
  mediator.syncFunctor(make_length, "=1234567890=", size1);
  mediator.syncFunctor(concat_many_strings, "aaa", "bbb", "uuu");
  mediator.syncFunctor(concat_and_make_length, "=1234567890=", "12345", size2);

  CPPUNIT_ASSERT_EQUAL(7, __strings.size());
  CPPUNIT_ASSERT_EQUAL("dummy", __strings.get(0));
  CPPUNIT_ASSERT_EQUAL("preserve:abc", __strings.get(1));
  CPPUNIT_ASSERT_EQUAL("make_zero:127", __strings.get(2));
  CPPUNIT_ASSERT_EQUAL("concat_strings:aaabbb", __strings.get(3));
  CPPUNIT_ASSERT_EQUAL("make_length:=1234567890=:3", __strings.get(4));
  CPPUNIT_ASSERT_EQUAL("concat_strings:aaabbbuuu", __strings.get(5));
  CPPUNIT_ASSERT_EQUAL("concat_and_make_length:=1234567890=12345:5", __strings.get(6));

  CPPUNIT_ASSERT_EQUAL(0, value);
  CPPUNIT_ASSERT_EQUAL(12, size1);
  CPPUNIT_ASSERT_EQUAL(17, size2);
}

namespace {
  struct MethodProbe {
    void dummyMethod(sk::rt::thread::Condition& condition) {
      dummy(condition);
    }

    void preserveMethod(sk::rt::thread::Condition& condition, const sk::util::String& s) {
      preserve(condition, s);
    }

    void make_zeroMethod(sk::rt::thread::Condition& condition, int& value) {
      make_zero(condition, value);
    }

    void concat_stringsMethod(sk::rt::thread::Condition& condition, const sk::util::String& s1, const sk::util::String& s2) {
      concat_strings(condition, s1, s2);
    }

    void make_lengthMethod(sk::rt::thread::Condition& condition, const sk::util::String& s, int& length) {
      make_length(condition, s, length);
    }

    void concat_many_stringsMethod(sk::rt::thread::Condition& condition, const sk::util::String& s1, const sk::util::String& s2, const std::string& s3) {
      concat_many_strings(condition, s1, s2, s3);
    }

    void concat_and_make_lengthMethod(sk::rt::thread::Condition& condition, const sk::util::String& s1, const std::string& s2, int& length) {
      concat_and_make_length(condition, s1, s2, length);
    }
  };
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_invoking_multi_param_methods()
{
  sk::rt::thread::ConditionMediator mediator(mutex());
  int value = 21;
  int size1 = 5;
  int size2 = 1;

  __strings.clear();
  MethodProbe probe;

  mediator.syncMethod(probe, &MethodProbe::dummyMethod);
  mediator.syncMethod(probe, &MethodProbe::preserveMethod, "abc");
  mediator.syncMethod(probe, &MethodProbe::make_zeroMethod, value);
  mediator.syncMethod(probe, &MethodProbe::concat_stringsMethod, "aaa", "bbb");
  mediator.syncMethod(probe, &MethodProbe::make_lengthMethod, "=1234567890=", size1);
  mediator.syncMethod(probe, &MethodProbe::concat_many_stringsMethod, "aaa", "bbb", "uuu");
  mediator.syncMethod(probe, &MethodProbe::concat_and_make_lengthMethod, "=1234567890=", "12345", size2);

  CPPUNIT_ASSERT_EQUAL(7, __strings.size());
  CPPUNIT_ASSERT_EQUAL("dummy", __strings.get(0));
  CPPUNIT_ASSERT_EQUAL("preserve:abc", __strings.get(1));
  CPPUNIT_ASSERT_EQUAL("make_zero:21", __strings.get(2));
  CPPUNIT_ASSERT_EQUAL("concat_strings:aaabbb", __strings.get(3));
  CPPUNIT_ASSERT_EQUAL("make_length:=1234567890=:5", __strings.get(4));
  CPPUNIT_ASSERT_EQUAL("concat_strings:aaabbbuuu", __strings.get(5));
  CPPUNIT_ASSERT_EQUAL("concat_and_make_length:=1234567890=12345:1", __strings.get(6));

  CPPUNIT_ASSERT_EQUAL(0, value);
  CPPUNIT_ASSERT_EQUAL(12, size1);
  CPPUNIT_ASSERT_EQUAL(17, size2);
}
