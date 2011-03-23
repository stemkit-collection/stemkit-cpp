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
test_non_blocking_fails_to_enter_when_locked()
{
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());
  mediator.setBlocking(false);

  sk::rt::Locker locker(_lockHolder.getMutable());
  bool method_invoked_indicator = false;
  CPPUNIT_ASSERT(mediator.synchronize(*this, &ConditionMediatorTest::ensureLocked, method_invoked_indicator) == false);
  CPPUNIT_ASSERT(method_invoked_indicator == false);
}
