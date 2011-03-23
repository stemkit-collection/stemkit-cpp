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
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/Locker.h>
#include <sk/rt/Thread.h>
#include <sys/time.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ConditionMediatorTest);

sk::rt::thread::tests::ConditionMediatorTest::
ConditionMediatorTest()
{
}

sk::rt::thread::tests::ConditionMediatorTest::
~ConditionMediatorTest()
{
}

void
sk::rt::thread::tests::ConditionMediatorTest::
setUp()
{
  _lockHolder.set(new sk::rt::Mutex);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
tearDown()
{
  _lockHolder.clear();
}

void
sk::rt::thread::tests::ConditionMediatorTest::
ensureLocked(sk::rt::thread::Condition& condition, bool& indicator)
{
  CPPUNIT_ASSERT_MESSAGE("Initial indicator value must be false", indicator == false);
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == true);

  indicator = true;
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_default_blocking_but_can_be_changed()
{
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());
  CPPUNIT_ASSERT(mediator.isBlocking() == true);
  mediator.setBlocking(false);
  CPPUNIT_ASSERT(mediator.isBlocking() == false);
  mediator.setBlocking(true);
  CPPUNIT_ASSERT(mediator.isBlocking() == true);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_synchronize_locks_invokes_and_unlocks()
{
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);

  bool method_invoked_indicator = false;
  CPPUNIT_ASSERT(mediator.synchronize(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == true);
  CPPUNIT_ASSERT(method_invoked_indicator == true);

  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_non_blocking_locks_when_available_and_fails_otherwise()
{
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());
  bool method_invoked_indicator = false;
  CPPUNIT_ASSERT(mediator.synchronize(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == true);
  CPPUNIT_ASSERT(method_invoked_indicator == true);

  mediator.setBlocking(false);
  sk::rt::Locker locker(_lockHolder.getMutable());
  method_invoked_indicator = false;

  CPPUNIT_ASSERT(mediator.synchronize(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == false);
  CPPUNIT_ASSERT(method_invoked_indicator == false);
}

namespace {
  struct Sampler : public virtual sk::rt::Runnable {
    Sampler(sk::rt::thread::ConditionMediator& m) 
      : mediator(m), moment(0), status(false) {}

    void registerTime(sk::rt::thread::Condition& condition) {
      moment = time(0);
    }

    void run() {
      status = mediator.synchronize(*this, &Sampler::registerTime);
    }
    volatile bool status;
    volatile time_t moment;
    sk::rt::thread::ConditionMediator& mediator;
  };
}

void
sk::rt::thread::tests::ConditionMediatorTest::
test_synchronize_waits_until_unlocked_then_invokes()
{
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());

  Sampler sampler(mediator);
  sk::rt::Thread thread(sampler);
  sk::rt::Locker locker(_lockHolder.getMutable());

  time_t now = time(0);
  thread.start();
  sleep(2);

  CPPUNIT_ASSERT(thread.isAlive() == true);

  locker.unlock();
  thread.join();

  CPPUNIT_ASSERT(thread.isAlive() == false);
  CPPUNIT_ASSERT(sampler.status == true);
  CPPUNIT_ASSERT(sampler.moment != 0);
  CPPUNIT_ASSERT((sampler.moment - now) >= 2);

  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);
}
