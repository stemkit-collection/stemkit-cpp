/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "ConditionMediatorEnsurePthreadsTest.h"

#include <sk/util/upcast.cxx>
#include <sk/rt/Mutex.h>
#include <sk/rt/thread/ConditionMediator.h>

#include "../../pthreads/ConditionMediator.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest);

sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest::
ConditionMediatorEnsurePthreadsTest()
{
}

sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest::
~ConditionMediatorEnsurePthreadsTest()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest::
setUp()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest::
tearDown()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorEnsurePthreadsTest::
testPthreadsConditionMediator()
{
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);

  CPPUNIT_ASSERT_NO_THROW(sk::util::upcast<pthreads::ConditionMediator>(mediator.getObject()));
}
