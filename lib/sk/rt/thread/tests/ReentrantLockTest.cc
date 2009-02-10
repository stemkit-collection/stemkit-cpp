/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "ReentrantLockTest.h"
#include <sk/util/SystemException.h>
#include <sk/rt/thread/ReentrantLock.h>
#include <sk/rt/Runnable.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::thread::tests::ReentrantLockTest);

sk::rt::thread::tests::ReentrantLockTest::
ReentrantLockTest()
{
}

sk::rt::thread::tests::ReentrantLockTest::
~ReentrantLockTest()
{
}

void
sk::rt::thread::tests::ReentrantLockTest::
setUp()
{
}

void
sk::rt::thread::tests::ReentrantLockTest::
tearDown()
{
}

void
sk::rt::thread::tests::ReentrantLockTest::
testLocking()
{
  sk::rt::thread::ReentrantLock lock;
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getHoldCount());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getHoldCount());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getHoldCount());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(3, lock.getHoldCount());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getHoldCount());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getHoldCount());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getHoldCount());

  try {
    lock.unlock();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::SystemException& exception) {
  }
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronize()
{
  sk::rt::thread::ReentrantLock lock;
  bool visited = false;

  struct Block : public virtual sk::rt::Runnable {
    Block(const ReentrantLock& lock, bool& visited)
      : _lock(lock), _visited(visited) {}

    void run() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _lock.isLocked());
      CPPUNIT_ASSERT_EQUAL(1, _lock.getHoldCount());
    }
    const ReentrantLock& _lock;
    bool& _visited;
  };

  CPPUNIT_ASSERT_EQUAL(false, visited);
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());

  lock.synchronize(Block(lock, visited));

  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(true, visited);
}

void 
sk::rt::thread::tests::ReentrantLockTest::
testBasics()
{
  {
    sk::rt::thread::ReentrantLock lock;
    lock.lock();
    lock.unlock();
  }
}
