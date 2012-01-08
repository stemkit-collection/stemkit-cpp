/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "ConditionMediatorEnsureGenericTest.h"

#include <sk/util/upcast.cxx>
#include <sk/rt/Mutex.h>
#include <sk/rt/thread/ConditionMediator.h>

#include "../generic/ConditionMediator.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ConditionMediatorEnsureGenericTest);

sk::rt::thread::tests::ConditionMediatorEnsureGenericTest::
ConditionMediatorEnsureGenericTest()
{
}

sk::rt::thread::tests::ConditionMediatorEnsureGenericTest::
~ConditionMediatorEnsureGenericTest()
{
}

void
sk::rt::thread::tests::ConditionMediatorEnsureGenericTest::
setUp()
{
}

void
sk::rt::thread::tests::ConditionMediatorEnsureGenericTest::
tearDown()
{
}

void
sk::rt::thread::tests::ConditionMediatorEnsureGenericTest::
testGenericConditionMediator()
{
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);

  CPPUNIT_ASSERT_NO_THROW(sk::util::upcast<generic::ConditionMediator>(mediator.getObject()));
}
