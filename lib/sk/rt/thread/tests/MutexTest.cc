/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "MutexTest.h"
#include <sk/rt/Mutex.h>
#include <sk/rt/Runnable.h>
#include <sk/rt/Locker.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::MutexTest);

sk::rt::thread::tests::MutexTest::
MutexTest()
{
}

sk::rt::thread::tests::MutexTest::
~MutexTest()
{
}

void
sk::rt::thread::tests::MutexTest::
setUp()
{
}

void
sk::rt::thread::tests::MutexTest::
tearDown()
{
}

void
sk::rt::thread::tests::MutexTest::
testLocking()
{
  sk::rt::Mutex mutex;
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());

  mutex.lock();
  CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());

  mutex.unlock();
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
}

namespace {
  struct Block {
    Block(const sk::rt::Mutex& mutex, bool& visited)
      : _mutex(mutex), _visited(visited) {}

    void operator()() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _mutex.isLocked());
    }
    const sk::rt::Mutex& _mutex;
    bool& _visited;
  };
}

void
sk::rt::thread::tests::MutexTest::
testSynchronize()
{
  sk::rt::Mutex mutex;
  bool visited = false;

  CPPUNIT_ASSERT_EQUAL(false, visited);
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());

  (sk::rt::Locker(mutex), Block(mutex, visited)());

  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, visited);
}

void
sk::rt::thread::tests::MutexTest::
testBasics()
{
  {
    sk::rt::Mutex mutex;
    mutex.lock();
    mutex.unlock();
  }
}
