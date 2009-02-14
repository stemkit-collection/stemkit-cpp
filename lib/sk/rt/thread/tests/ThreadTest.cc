/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include "ThreadTest.h"
#include <sk/rt/Thread.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ThreadTest);

sk::rt::thread::tests::ThreadTest::
ThreadTest()
{
}

sk::rt::thread::tests::ThreadTest::
~ThreadTest()
{
}

void
sk::rt::thread::tests::ThreadTest::
setUp()
{
  sk::rt::Thread::reset();
}

void
sk::rt::thread::tests::ThreadTest::
tearDown()
{
  sk::rt::Thread::reset();
}

void
sk::rt::thread::tests::ThreadTest::
testCreateDefault()
{
  sk::rt::Thread thread;

  CPPUNIT_ASSERT_EQUAL("Thread-1", thread.getName());
  CPPUNIT_ASSERT(thread.getState() == sk::rt::thread::State::SK_T_NEW);
  CPPUNIT_ASSERT_EQUAL(true, thread.isRegular());
  CPPUNIT_ASSERT_EQUAL(false, thread.isMain());
  CPPUNIT_ASSERT_EQUAL(false, thread.isService());
}