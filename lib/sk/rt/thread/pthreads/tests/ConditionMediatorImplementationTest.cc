/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ConditionMediatorImplementationTest.h"

#include <sk/util/upcast.cxx>
#include <sk/rt/Mutex.h>
#include <sk/rt/thread/ConditionMediator.h>
#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

#include "../../pthreads/ConditionMediator.h"
#include "../../generic/ConditionMediator.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest);

sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
ConditionMediatorImplementationTest()
{
}

sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
~ConditionMediatorImplementationTest()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
setUp()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
tearDown()
{
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
testDefaultImplementation()
{
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);

  CPPUNIT_ASSERT_NO_THROW(sk::util::upcast<pthreads::ConditionMediator>(mediator.getObject()));
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
testGenericImplementation()
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <scope name='sk::rt::thread'>\n\
          <property name='generic-condition-mediator' value='true' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);

  CPPUNIT_ASSERT_NO_THROW(sk::util::upcast<generic::ConditionMediator>(mediator.getObject()));
}

void
sk::rt::thread::pthreads::tests::ConditionMediatorImplementationTest::
testPthreadsImplementation()
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator("\n\
      <scope name='app'>\n\
        <scope name='sk::rt::thread'>\n\
          <property name='generic-condition-mediator' value='false' />\n\
        </scope>\n\
      </scope>\n\
    ")
  );
  sk::rt::Mutex mutex;
  sk::rt::thread::ConditionMediator mediator(mutex);

  CPPUNIT_ASSERT_NO_THROW(sk::util::upcast<pthreads::ConditionMediator>(mediator.getObject()));
}
