/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "DispatcherTest.h"
#include "../Dispatcher.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::DispatcherTest);

sk::rt::thread::tests::DispatcherTest::
DispatcherTest()
{
}

sk::rt::thread::tests::DispatcherTest::
~DispatcherTest()
{
}

void
sk::rt::thread::tests::DispatcherTest::
setUp()
{
}

void
sk::rt::thread::tests::DispatcherTest::
tearDown()
{
}

void
sk::rt::thread::tests::DispatcherTest::
testSequence()
{
  sk::rt::thread::Dispatcher dispatcher;
  CPPUNIT_ASSERT_EQUAL(1LL, dispatcher.makeSequence());
  CPPUNIT_ASSERT_EQUAL(2LL, dispatcher.makeSequence());
  CPPUNIT_ASSERT_EQUAL(3LL, dispatcher.makeSequence());
}

void 
sk::rt::thread::tests::DispatcherTest::
testMainInstance()
{
  long long id = Dispatcher::main().getId();
  CPPUNIT_ASSERT(id == Dispatcher::main().getId());
  CPPUNIT_ASSERT(Dispatcher::main().getId() == Dispatcher::main().getId());

  CPPUNIT_ASSERT_EQUAL(1LL, Dispatcher::main().makeSequence());
  CPPUNIT_ASSERT_EQUAL(2LL, Dispatcher::main().makeSequence());
  CPPUNIT_ASSERT_EQUAL(3LL, Dispatcher::main().makeSequence());

  Dispatcher::cleanup();

  CPPUNIT_ASSERT(id != Dispatcher::main().getId());
  CPPUNIT_ASSERT_EQUAL(1LL, Dispatcher::main().makeSequence());
}


