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
ensureLocked(sk::rt::thread::Condition& condition)
{
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == true);
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
test_synchronize_locks_and_unlocks()
{
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);
  sk::rt::thread::ConditionMediator mediator(_lockHolder.getMutable());
  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);

  mediator.synchronize(*this, &ConditionMediatorTest::ensureLocked);

  CPPUNIT_ASSERT(_lockHolder.get().isLocked() == false);
}
