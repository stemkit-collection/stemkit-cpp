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
  CPPUNIT_ASSERT_EQUAL(uint64_t(1), dispatcher.makeSequence());
  CPPUNIT_ASSERT_EQUAL(uint64_t(2), dispatcher.makeSequence());
  CPPUNIT_ASSERT_EQUAL(uint64_t(3), dispatcher.makeSequence());
}

void 
sk::rt::thread::tests::DispatcherTest::
testMainInstance()
{
  uint64_t id = Dispatcher::main().getId();
  CPPUNIT_ASSERT(id == Dispatcher::main().getId());
  CPPUNIT_ASSERT(Dispatcher::main().getId() == Dispatcher::main().getId());

  CPPUNIT_ASSERT_EQUAL(uint64_t(1), Dispatcher::main().makeSequence());
  CPPUNIT_ASSERT_EQUAL(uint64_t(2), Dispatcher::main().makeSequence());
  CPPUNIT_ASSERT_EQUAL(uint64_t(3), Dispatcher::main().makeSequence());

  Dispatcher::reset();

  CPPUNIT_ASSERT_EQUAL(uint64_t(1), Dispatcher::main().makeSequence());
}


