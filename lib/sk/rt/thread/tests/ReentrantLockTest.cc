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
#include <sk/util/Holder.cxx>

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
  _lockHolder.clear();
}

void
sk::rt::thread::tests::ReentrantLockTest::
testLocking()
{
  sk::rt::thread::ReentrantLock lock;
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getCounter());

  lock.lock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(3, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(2, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(true, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(1, lock.getCounter());

  lock.unlock();
  CPPUNIT_ASSERT_EQUAL(false, lock.isLocked());
  CPPUNIT_ASSERT_EQUAL(0, lock.getCounter());

  try {
    lock.unlock();
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::util::SystemException& exception) {
  }
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeBlock()
{
  sk::rt::thread::ReentrantLock lock;
  bool visited = false;

  struct Block : public virtual sk::rt::Runnable {
    Block(const ReentrantLock& lock, bool& visited)
      : _lock(lock), _visited(visited) {}

    void run() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _lock.isLocked());
      CPPUNIT_ASSERT_EQUAL(1, _lock.getCounter());
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
criticalSectionWithoutParam()
{
  _visited = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeMethodWithoutParam()
{
  _visited = false;
  _lockHolder.set(new ReentrantLock);
  _lockHolder.get().synchronize(*this, &ReentrantLockTest::criticalSectionWithoutParam);

  CPPUNIT_ASSERT_EQUAL(true, _visited);
}

void 
sk::rt::thread::tests::ReentrantLockTest::
criticalSectionWithParam(bool& flag)
{
  flag = true;
  CPPUNIT_ASSERT_EQUAL(true, _lockHolder.get().isLocked());
  CPPUNIT_ASSERT_EQUAL(1, _lockHolder.get().getCounter());
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeMethodWithParam()
{
  bool visited = false;
  _lockHolder.set(new ReentrantLock);
  _lockHolder.get().synchronize(*this, &ReentrantLockTest::criticalSectionWithParam, visited);

  CPPUNIT_ASSERT_EQUAL(true, visited);
}

namespace {
  bool global_flag = false;
  void f() {
    global_flag = true;
  }
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeFunction()
{
  global_flag = false;

  ReentrantLock lock;
  lock.synchronize(f);

  CPPUNIT_ASSERT_EQUAL(true, global_flag);
}

namespace {
  struct Block {
    Block(const sk::rt::thread::ReentrantLock& lock, bool& visited)
      : _lock(lock), _visited(visited) {}

    void operator()() const {
      _visited = true;

      CPPUNIT_ASSERT_EQUAL(true, _lock.isLocked());
      CPPUNIT_ASSERT_EQUAL(1, _lock.getCounter());
    }
    const sk::rt::thread::ReentrantLock& _lock;
    bool& _visited;
  };
}

void
sk::rt::thread::tests::ReentrantLockTest::
testSynchronizeFunctor()
{
  sk::rt::thread::ReentrantLock lock;
  bool visited = false;

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
