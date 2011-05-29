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

void 
sk::rt::thread::tests::ConditionMediatorTest::
announceCondition(sk::rt::thread::Condition& condition, int channel)
{
  condition.on(channel).announce();
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
  mediator.syncMethod(*this, &ConditionMediatorTest::announceCondition, 0);
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
  mediator.syncMethod(*this, &ConditionMediatorTest::announceCondition, int(EVENT_1));
  sk::rt::Thread::sleep(1000);

  CPPUNIT_ASSERT(t1.isAlive() == false);
  CPPUNIT_ASSERT(t2.isAlive() == true);

  CPPUNIT_ASSERT(w1.triggered == true);
  CPPUNIT_ASSERT(w2.triggered == false);

  w2.event = true;
  mediator.syncMethod(*this, &ConditionMediatorTest::announceCondition, int(EVENT_2));
  sk::rt::Thread::sleep(1000);

  CPPUNIT_ASSERT(t2.isAlive() == false);
  CPPUNIT_ASSERT(w2.triggered == true);
}
