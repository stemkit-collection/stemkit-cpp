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
#include <sk/rt/thread/Mutex.h>
#include <sk/rt/Runnable.h>

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
  sk::rt::thread::Mutex mutex;
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  CPPUNIT_ASSERT_EQUAL(false, mutex.isOwner());

  mutex.lock();
  CPPUNIT_ASSERT_EQUAL(true, mutex.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, mutex.isOwner());

  mutex.unlock();
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  CPPUNIT_ASSERT_EQUAL(false, mutex.isOwner());
}

void
sk::rt::thread::tests::MutexTest::
testSynchronize()
{
  sk::rt::thread::Mutex mutex;
  bool visited = false;

  struct Block : public virtual sk::rt::Runnable {
    Block(const Mutex& mutex, bool& visited)
      : _mutex(mutex), _visited(visited) {}

    void run() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _mutex.isLocked());
      CPPUNIT_ASSERT_EQUAL(true, _mutex.isOwner());
    }
    const Mutex& _mutex;
    bool& _visited;
  };

  CPPUNIT_ASSERT_EQUAL(false, visited);
  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());

  mutex.synchronize(Block(mutex, visited));

  CPPUNIT_ASSERT_EQUAL(false, mutex.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, visited);
}

